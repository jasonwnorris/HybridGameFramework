// GlyphFont.cpp

// SDL2 Includes
#include <SDL2/SDL.h>
// HGF Includes
#include <HGF/GlyphFont.hpp>
// HM Includes
#include <HM/Math.hpp>
// STL Includes
#include <algorithm>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 Rmask = 0xff000000;
Uint32 Gmask = 0x00ff0000;
Uint32 Bmask = 0x0000ff00;
Uint32 Amask = 0x000000ff;
#else
Uint32 Rmask = 0x000000ff;
Uint32 Gmask = 0x0000ff00;
Uint32 Bmask = 0x00ff0000;
Uint32 Amask = 0xff000000;
#endif

namespace HGF
{
  GlyphFont::GlyphFont()
  {
  }

  GlyphFont::~GlyphFont()
  {
    if (m_IsLoaded)
    {
      Unload();
    }
  }

  float GlyphFont::GetCharacterSpacing(unsigned int p_Character) const
  {
    for (const Glyph& glyph : m_Glyphs)
    {
      if (glyph.Character == p_Character)
      {
        return static_cast<float>(glyph.Advance + glyph.MinX);
      }
    }

    return 0.0f;
  }

  float GlyphFont::GetLineSpacing() const
  {
    return static_cast<float>(m_LineSkip);
  }

  const Texture& GlyphFont::GetTexture() const
  {
    return m_Texture;
  }

  HM::Rectanglef GlyphFont::GetCharacterBounds(unsigned int p_Character) const
  {
    for (const Glyph& glyph : m_Glyphs)
    {
      if (glyph.Character == p_Character)
      {
        return HM::Rectanglef(glyph.VisualX, glyph.VisualY, glyph.VisualWidth, glyph.VisualHeight);
      }
    }

    return HM::Rectanglef::Empty;
  }

  void GlyphFont::MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions)
  {
  }

  bool GlyphFont::Load(const std::string& p_Filename, const GlyphFontOptions& p_Options)
  {
    // Open the font.
    TTF_Font* font = TTF_OpenFont(p_Filename.c_str(), p_Options.Size);
    //TTF_Font* font = TTF_OpenFont(p_Filename.c_str(), static_cast<int>(p_Size));
    if (font == nullptr)
    {
      SDL_Log("[HGF::GlyphFont::Load] Failed to load TTF file: %s", SDL_GetError());
      return false;
    }

    // Set options.
    TTF_SetFontStyle(font, static_cast<int>(p_Options.Style));
    TTF_SetFontOutline(font, p_Options.Outline);
    TTF_SetFontHinting(font, static_cast<int>(p_Options.Hinting));
    TTF_SetFontKerning(font, p_Options.UseKerning ? 1 : 0);

    // Collect metrics.
    m_Height = TTF_FontHeight(font);
    m_Ascent = TTF_FontAscent(font);
    m_Descent = TTF_FontDescent(font);
    m_LineSkip = TTF_FontLineSkip(font);
    m_Faces = TTF_FontFaces(font);
    m_IsFixedWidth = TTF_FontFaceIsFixedWidth(font) > 0;
    char* faceFamilyName = TTF_FontFaceFamilyName(font);
    if (faceFamilyName != nullptr)
    {
      m_FaceFamilyName.assign(faceFamilyName);
    }
    char* faceStyleName = TTF_FontFaceStyleName(font);
    if (faceStyleName != nullptr)
    {
      m_FaceStyleName.assign(faceStyleName);
    }

    // Collect glyph metrics.
    const unsigned short maxGlyphs = 65535;
    for (unsigned short ch = 0; ch < maxGlyphs; ++ch)
    {
      int index = TTF_GlyphIsProvided(font, ch);
      if (index > 0)
      {
        Glyph glyph;
        glyph.Character = ch;
        glyph.Index = index;

        if (TTF_GlyphMetrics(font, ch, &glyph.MinX, &glyph.MaxX, &glyph.MinY, &glyph.MaxY, &glyph.Advance) < 0)
        {
          SDL_Log("[HGF::GlyphFont::Load] Failed to gather glyph metrics: %s", SDL_GetError());
          continue;
        }

        if ((glyph.MaxX - glyph.MinX) <= 0 || (glyph.MaxY - glyph.MinY) <= 0)
        {
          continue;
        }

        if (TTF_SizeUNICODE(font, &ch, &glyph.SpacialWidth, &glyph.SpacialHeight) < 0)
        {
          SDL_Log("[HGF::GlyphFont::Load] Failed to gather spacial sizes: %s", SDL_GetError());
          continue;
        }

        if (glyph.SpacialWidth <= 0 || glyph.SpacialHeight <= 0)
        {
          continue;
        }

        static const SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderGlyph_Blended(font, ch, color);
        if (surface == nullptr)
        {
          SDL_Log("[HGF::GlyphFont::Load] Failed to render TTF surface: %s", SDL_GetError());
        }

        glyph.Surface = TrimSurface(surface);
        glyph.Surface = surface;
        glyph.VisualWidth = glyph.Surface->w;
        glyph.VisualHeight = glyph.Surface->h;

        m_Glyphs.push_back(glyph);
      }
    }

    // Close the font.
    TTF_CloseFont(font);

    // Sort glyphs by height.
    std::sort(m_Glyphs.begin(), m_Glyphs.end(), [](const Glyph& glyphA, const Glyph& glyphB) {
      return glyphA.VisualHeight > glyphB.VisualHeight;
    });

    // Pack glyphs into area.
    int offsetX = 0;
    int offsetY = 0;
    int sizeWidth = HeuristicWidth();
    int maxHeight = 0;
    for (Glyph& glyph : m_Glyphs)
    {
      if (offsetX + glyph.VisualWidth > sizeWidth)
      {
        offsetX = 0;
        offsetY += maxHeight;
        maxHeight = 0;
      }
      glyph.VisualX = offsetX;
      glyph.VisualY = offsetY;
      offsetX += glyph.VisualWidth;
      maxHeight = HM::Math::Max(glyph.VisualHeight, maxHeight);
    }
    int sizeHeight = MakeValidTextureSize(offsetY + maxHeight);

    // Collapse glyphs to single surface.
    SDL_Surface* canvas = SDL_CreateRGBSurface(0, sizeWidth, sizeHeight, 32, Rmask, Gmask, Bmask, Amask);
    for (const Glyph& glyph : m_Glyphs)
    {
      SDL_Rect destination = {
        glyph.VisualX,
        glyph.VisualY,
        glyph.VisualWidth,
        glyph.VisualHeight
      };
      SDL_BlitSurface(glyph.Surface, nullptr, canvas, &destination);
    }

    // Create texture from surface.
    std::vector<Color> pixels;
    for (int y = 0; y < sizeHeight; ++y)
    {
      for (int x = 0; x < sizeWidth; ++x)
      {
        Uint8 red;
        Uint8 green;
        Uint8 blue;
        Uint8 alpha;
        GetPixelColor(canvas, x, y, red, green, blue, alpha);

        pixels.push_back(Color(static_cast<int>(red),
                               static_cast<int>(green),
                               static_cast<int>(blue),
                               static_cast<int>(alpha)));
      }
    }
    TextureOptions textureOptions;
    textureOptions.Interpolation = TextureInterpolation::Linear;
    textureOptions.Wrapping = TextureWrapping::ClampToEdge;
    m_Texture.FromPixelColors(sizeWidth, sizeHeight, pixels, textureOptions);

    // Save out surface for testing.
    if (SDL_SaveBMP(canvas, "canvas.bmp") < 0)
    {
      SDL_Log("Failed to write surface to file: %s", SDL_GetError());
    }

    // Clean up.
    for (Glyph& glyph : m_Glyphs)
    {
      SDL_FreeSurface(glyph.Surface);
    }
    SDL_FreeSurface(canvas);

    return true;
  }

  void GlyphFont::Unload()
  {
    m_Texture.Unload();

    m_IsLoaded = false;
  }

  int GlyphFont::HeuristicWidth()
  {
    int totalSize = 0;

    for (const Glyph& glyph : m_Glyphs)
    {
      totalSize += glyph.VisualWidth * glyph.VisualHeight;
    }

    return MakeValidTextureSize(static_cast<int>(sqrtf(totalSize)), true);
  }

  int GlyphFont::MakeValidTextureSize(int p_Value, bool p_IsPOT)
  {
    const int blockSize = 4;

    if (p_IsPOT)
    {
      int value = blockSize;

      while (value < p_Value)
      {
        value <<= 1;
      }

      return value;
    }

    return p_Value;
  }

  SDL_Surface* GlyphFont::TrimSurface(SDL_Surface* surface)
  {
    int width = surface->w;
    int height = surface->h;

    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;

    // Find the first visible top pixel.
    int top = 0;
    bool foundTop = false;
    while (top < height)
    {
      for (int x = 0; x < width; ++x)
      {
        GetPixelColor(surface, x, top, red, green, blue, alpha);
        if (alpha == 0)
        {
          foundTop = true;
          break;
        }
      }

      if (foundTop)
      {
        break;
      }
      else
      {
        ++top;
      }
    }

    // Find the first visible bottom pixel.
    int bottom = width - 1;
    bool foundBottom = false;
    while (bottom >= 0)
    {
      for (int x = 0; x < width; ++x)
      {
        GetPixelColor(surface, x, bottom, red, green, blue, alpha);
        if (alpha == 0)
        {
          foundBottom = true;
          break;
        }
      }

      if (foundBottom)
      {
        break;
      }
      else
      {
        --bottom;
      }
    }

    // Find the first visible left pixel.
    int left = 0;
    bool foundLeft = false;
    while (left < width)
    {
      for (int y = 0; y < height; ++y)
      {
        GetPixelColor(surface, left, y, red, green, blue, alpha);
        if (alpha == 0)
        {
          foundLeft = true;
          break;
        }
      }

      if (foundLeft)
      {
        break;
      }
      else
      {
        ++left;
      }
    }

    // Find the first visible right pixel.
    int right = height - 1;
    bool foundRight = false;
    while (right >= 0)
    {
      for (int y = 0; y < height; ++y)
      {
        GetPixelColor(surface, right, y, red, green, blue, alpha);
        if (alpha == 0)
        {
          foundRight = true;
          break;
        }
      }

      if (foundRight)
      {
        break;
      }
      else
      {
        --right;
      }
    }

    // Create the new surface.
    int resizedWidth = right - left + 1;
    int resizedHeight = bottom - top + 1;
    SDL_Rect sourceRect = { top, left, resizedWidth, resizedHeight };
    SDL_Surface* resizedSurface = SDL_CreateRGBSurface(0, resizedWidth, resizedHeight, surface->format->BitsPerPixel, Rmask, Gmask, Bmask, Amask);
    SDL_BlitSurface(surface, &sourceRect, resizedSurface, nullptr);
    SDL_FreeSurface(surface);

    return resizedSurface;
  }

  void GlyphFont::GetPixelColor(SDL_Surface* surface, int x, int y, Uint8& red, Uint8& green, Uint8& blue, Uint8& alpha)
  {
    int bpp = surface->format->BytesPerPixel;
    Uint8* ptr = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    Uint32 pixel = 0;

    switch(bpp)
    {
      case 1:
        pixel = *ptr;
        break;
      case 2:
        pixel = *(Uint16*)ptr;
        break;
      case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        pixel = ptr[0] << 16 | ptr[1] << 8 | ptr[2];
#else
        pixel = ptr[0] | ptr[1] << 8 | ptr[2] << 16;
#endif
        break;
      case 4:
        pixel = *(Uint32*)ptr;
        break;
      default:
        pixel = 0;
        break;
    }

    SDL_GetRGBA(pixel, surface->format, &red, &green, &blue, &alpha);
  }
}
