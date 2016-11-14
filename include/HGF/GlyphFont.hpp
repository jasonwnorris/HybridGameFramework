// GlyphFont.hpp

#ifndef __HGF_GLYPHFONT_HPP__
#define __HGF_GLYPHFONT_HPP__

// HGF Includes
#include <HGF/Glyph.hpp>
#include <HGF/GlyphFontOptions.hpp>
#include <HGF/IFont.hpp>
#include <HGF/ILoadable.hpp>

namespace HGF
{
  class GlyphFont : public IFont, public ILoadable<GlyphFontOptions>
  {
    public:
      GlyphFont();
      ~GlyphFont();

      float GetCharacterSpacing(unsigned int p_Character) const override;
      float GetLineSpacing() const override;

      const Texture& GetTexture() const override;
      HM::Rectanglef GetCharacterBounds(unsigned int p_Character) const override;

      void MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions) override;

      bool Load(const std::string& p_Filename, const GlyphFontOptions& p_Options) override;
      void Unload() override;

    private:
      int HeuristicWidth();
      int MakeValidTextureSize(int p_Value, bool p_IsPOT = true);
      SDL_Surface* TrimSurface(SDL_Surface* surface);
      void GetPixelColor(SDL_Surface* surface, int x, int y, Uint8& red, Uint8& green, Uint8& blue, Uint8& alpha);

    private:
      Texture m_Texture;
      int m_Height;
      int m_Ascent;
      int m_Descent;
      int m_LineSkip;
      long m_Faces;
      bool m_IsFixedWidth;
      std::string m_FaceFamilyName;
      std::string m_FaceStyleName;
      std::vector<Glyph> m_Glyphs;
  };
}

#endif
