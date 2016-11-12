// Texture.hpp

#ifndef __HGF_TEXTURE_HPP__
#define __HGF_TEXTURE_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>
// HGF Includes
#include <HGF/Color.hpp>
#include <HGF/TextureInterpolation.hpp>
#include <HGF/TextureWrapping.hpp>
// STL Includes
#include <string>
#include <vector>

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
      bool GetPixelColor(unsigned int p_X, unsigned int p_Y, Color& p_Color);

      bool FromPixelColors(unsigned int p_Width, unsigned int p_Height, std::vector<Color> p_Colors, TextureInterpolation p_Interpolation, TextureWrapping p_Wrapping);
      bool Load(const std::string& p_Filename, TextureInterpolation p_Interpolation, TextureWrapping p_Wrapping);
      void Unload();

    private:
      bool CreateFromPixelData(void* p_PixelData);
      bool ReadColorDataFromSurface(SDL_Surface* p_Surface, unsigned int p_X, unsigned int p_Y, Color& p_Color);

      bool m_IsLoaded;
      unsigned int m_ID;
      unsigned int m_Width;
      unsigned int m_Height;
      unsigned int m_BytesPerPixel;
      TextureInterpolation m_Interpolation;
      TextureWrapping m_Wrapping;
      std::vector<Color> m_Colors;
  };
}

#endif
