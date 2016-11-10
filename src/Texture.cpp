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

  TextureInterpolation Texture::GetInterpolation() const
  {
    return m_Interpolation;
  }

  TextureWrapping Texture::GetWrapping() const
  {
    return m_Wrapping;
  }

  bool Texture::Load(const std::string& p_Filename, TextureInterpolation p_Interpolation, TextureWrapping p_Wrapping)
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
    m_Interpolation = p_Interpolation;
    m_Wrapping = p_Wrapping;

    // Check dimensions.
    if (!HM::Math::IsPowerOfTwo(m_Width))
    {
      SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::Load] Texture width is not a power of two.");
    }
    if (!HM::Math::IsPowerOfTwo(m_Height))
    {
      SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::Load] Texture height is not a power of two.");
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
        SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[HGF::Texture::Load] Pixel data does not use true color.");
        return false;
    }

    // Generate and create the texture.
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    // Set scaling interpolation.
    switch (m_Interpolation)
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
    switch (m_Wrapping)
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
}
