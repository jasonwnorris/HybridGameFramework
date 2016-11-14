// Texture.cpp

// SDL2 Includes
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
// HGF Includes
#include <HGF/Texture.hpp>
// HM Includes
#include <HM/Math.hpp>

namespace HGF
{
  Texture::Texture()
  {
    m_ID = -1;
    m_IsLoaded = false;
  }

  Texture::~Texture()
  {
    if (m_IsLoaded)
    {
      Unload();
    }
  }

  unsigned int Texture::GetID() const
  {
    return m_ID;
  }

  unsigned int Texture::GetWidth() const
  {
    return m_Width;
  }

  unsigned int Texture::GetHeight() const
  {
    return m_Height;
  }

  unsigned int Texture::GetBytesPerPixel() const
  {
    return m_BytesPerPixel;
  }

  const TextureInterpolation& Texture::GetInterpolation() const
  {
    return m_Options.Interpolation;
  }

  const TextureWrapping& Texture::GetWrapping() const
  {
    return m_Options.Wrapping;
  }

  bool Texture::GetPixelColor(unsigned int p_X, unsigned int p_Y, Color& p_Color)
  {
    // Check if within bounds.
    if (p_X >= m_Width || p_Y >= m_Height)
    {
      SDL_Log("[HGF::Texture::GetPixelColor] Coordinates are out of texture bounds.");
      return false;
    }

    p_Color = m_Colors[p_X + p_Y * m_Width];

    return true;
  }

  bool Texture::FromPixelColors(unsigned int p_Width, unsigned int p_Height, std::vector<Color> p_Colors, const TextureOptions& p_Options)
  {
    // Check if already loaded.
    if (m_IsLoaded)
    {
      SDL_Log("[HGF::Texture::FromPixelColors] Texture is already loaded.");
      return false;
    }

    // Collect metrics.
    m_Width = p_Width;
    m_Height = p_Height;
    m_BytesPerPixel = 4;
    m_Options = p_Options;

    // Copy colors to composite pixels.
    std::vector<unsigned int> pixels;
    for (const Color& color : p_Colors)
    {
      pixels.push_back(color.GetAsComposite());

      m_Colors.push_back(color);
    }

    // Create the texture.
    if (!CreateFromPixelData(static_cast<void*>(&pixels.front())))
    {
      return false;
    }

    return (m_IsLoaded = true);
  }

  bool Texture::Load(const std::string& p_Filename, const TextureOptions& p_Options)
  {
    // Check if already loaded.
    if (m_IsLoaded)
    {
      SDL_Log("[HGF::Texture::Load] Texture is already loaded.");
      return false;
    }

    // Load the surface.
    SDL_Surface* surface = IMG_Load(p_Filename.c_str());
    if (surface == nullptr)
    {
      SDL_Log("[HGF::Texture::Load] Failed to load image file \"%s\": %s", p_Filename.c_str(), SDL_GetError());
      return false;
    }

    // Collect metrics.
    m_Width = surface->w;
    m_Height = surface->h;
    m_BytesPerPixel = surface->format->BytesPerPixel;
    m_Options = p_Options;

    // Gather pixel colors.
    Color color;
    for (int y = 0; y < m_Height; ++y)
    {
      for (int x = 0; x < m_Width; ++x)
      {
        if (ReadColorDataFromSurface(surface, x, y, color))
        {
          m_Colors.push_back(color);
        }
      }
    }

    // Create the texture.
    if (!CreateFromPixelData(surface->pixels))
    {
      return false;
    }

    // Free the loaded surface.
    SDL_FreeSurface(surface);

    return (m_IsLoaded = true);
  }

  void Texture::Unload()
  {
    if (!m_IsLoaded)
    {
      SDL_Log("[HGF::Texture::Unload] Texture not loaded. Doing nothing.");
    }
    else
    {
      // Delete the texture.
      if (m_ID != -1)
      {
        glDeleteTextures(1, &m_ID);
      }

      m_IsLoaded = false;
    }
  }

  bool Texture::CreateFromPixelData(void* p_PixelData)
  {
    // Check dimensions.
    if (!HM::Math::IsPowerOfTwo(m_Width))
    {
      SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::CreateFromPixelData] Width is not a power of two.");
    }
    if (!HM::Math::IsPowerOfTwo(m_Height))
    {
      SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::CreateFromPixelData] Height is not a power of two.");
    }

    // Determine color mode.
    GLenum format = 0;
    switch (m_BytesPerPixel)
    {
      case 3:
        format = GL_RGB;
        break;
      case 4:
        format = GL_RGBA;
        break;
      default:
        SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::CreateFromPixelData] Pixel data does not use true color.");
        return false;
    }

    // Generate and create the texture.
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, p_PixelData);

    // Set scaling interpolation.
    switch (m_Options.Interpolation)
    {
      case TextureInterpolation::Linear:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
      case TextureInterpolation::Nearest:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    }

    // Set edge wrapping.
    switch (m_Options.Wrapping)
    {
      case TextureWrapping::ClampToBorder:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        static float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
        break;
      case TextureWrapping::ClampToEdge:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
      case TextureWrapping::Repeat:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
      case TextureWrapping::RepeatMirrored:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
    }

    // Unbind the texture.
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
  }

  bool Texture::ReadColorDataFromSurface(SDL_Surface* p_Surface, unsigned int p_X, unsigned int p_Y, Color& p_Color)
  {
    // Check if within bounds.
    if (p_X >= m_Width || p_Y >= m_Height)
    {
      SDL_Log("[HGF::Texture::ReadColorDataFromSurface] Coordinates are out of texture bounds.");
      return false;
    }

    Uint32 pixel = -1;
    Uint8* pointer = static_cast<Uint8*>(p_Surface->pixels) + p_Y * p_Surface->pitch + p_X * m_BytesPerPixel;

    switch (m_BytesPerPixel)
    {
      case 1:
        pixel = *pointer;
        break;
      case 2:
        pixel = *(Uint16*)pointer;
        break;
      case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        pixel = pointer[0] << 16 | pointer[1] << 8 | pointer[2];
#else
        pixel = pointer[0] | pointer[1] << 8 | pointer[2] << 16;
#endif
        break;
      case 4:
        pixel = *(Uint32*)pointer;
        break;
      default:
        SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::ReadColorDataFromSurface] Pixel data has unknown color format.");
        return false;
    }

    p_Color.SetFromComposite(pixel);

    return true;
  }
}
