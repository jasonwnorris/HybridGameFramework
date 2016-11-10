// Texture.hpp

#ifndef __HGF_TEXTURE_HPP__
#define __HGF_TEXTURE_HPP__

// HGF Includes
#include <HGF/TextureInterpolation.hpp>
#include <HGF/TextureWrapping.hpp>
// STL Includes
#include <string>

namespace HGF
{
  class Texture
  {
    public:
      Texture();
      ~Texture();

      unsigned int GetID() const;
      unsigned int GetWidth() const;
      unsigned int GetHeight() const;
      unsigned int GetBytesPerPixel() const;
      TextureInterpolation GetInterpolation() const;
      TextureWrapping GetWrapping() const;

      bool Load(const std::string& p_Filename, TextureInterpolation p_Interpolation, TextureWrapping p_Wrapping);
      void Unload();

    private:
      bool m_IsLoaded;
      unsigned int m_ID;
      unsigned int m_Width;
      unsigned int m_Height;
      unsigned int m_BytesPerPixel;
      TextureInterpolation m_Interpolation;
      TextureWrapping m_Wrapping;
  };
}

#endif
