// SpriteFont.hpp

#ifndef __HGF_SPRITEFONT_HPP__
#define __HGF_SPRITEFONT_HPP__

// HGF Includes
#include <HGF/IFont.hpp>
#include <HGF/ILoadable.hpp>
#include <HGF/SpriteFontOptions.hpp>

namespace HGF
{
  class SpriteFont : public IFont, public ILoadable<SpriteFontOptions>
  {
    public:
      SpriteFont();
      ~SpriteFont();

      float GetCharacterSpacing(unsigned int p_Character) const override;
      float GetLineSpacing() const override;

      const Texture& GetTexture() const override;
      HM::Rectanglef GetCharacterBounds(unsigned int p_Character) const override;

      void MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions) override;

      bool Load(const std::string& p_Filename, const SpriteFontOptions& p_Options) override;
      void Unload() override;

    private:
      Texture m_Texture;
      SpriteFontOptions m_Options;
  };
}

#endif
