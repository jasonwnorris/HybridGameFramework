// Texture.hpp

#ifndef __HGF_TEXTURE_HPP__
#define __HGF_TEXTURE_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>
// HGF Includes
#include <HGF/Color.hpp>
#include <HGF/ILoadable.hpp>
#include <HGF/TextureOptions.hpp>
// STL Includes
#include <string>
#include <vector>

namespace HGF
{
  class Texture : public ILoadable<TextureOptions>
  {
    public:
      Texture();
      ~Texture();

      unsigned int GetID() const;
      unsigned int GetWidth() const;
      unsigned int GetHeight() const;
      unsigned int GetBytesPerPixel() const;
      const TextureInterpolation& GetInterpolation() const;
      const TextureWrapping& GetWrapping() const;
      bool GetPixelColor(unsigned int p_X, unsigned int p_Y, Color& p_Color);

      bool FromPixelColors(unsigned int p_Width, unsigned int p_Height, std::vector<Color> p_Colors, const TextureOptions& p_Options);

      bool Load(const std::string& p_Filename, const TextureOptions& p_Options);
      void Unload();

    private:
      bool CreateFromPixelData(void* p_PixelData);
      bool ReadColorDataFromSurface(SDL_Surface* p_Surface, unsigned int p_X, unsigned int p_Y, Color& p_Color);

      bool m_IsLoaded;
      unsigned int m_ID;
      unsigned int m_Width;
      unsigned int m_Height;
      unsigned int m_BytesPerPixel;
      TextureOptions m_Options;
      std::vector<Color> m_Colors;
  };
}

#endif
