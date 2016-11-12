// SpriteFont.hpp

#ifndef __HGF_SPRITEFONT_HPP__
#define __HGF_SPRITEFONT_HPP__

// HGF Includes
#include <HGF/Texture.hpp>
// HM Includes
#include <HM/Rectangle.hpp>
#include <HM/Vector2.hpp>
// STL Includes
#include <string>

namespace HGF
{
  class SpriteFont
  {
    public:
      SpriteFont();
      ~SpriteFont();

      float GetCharacterSpacing(unsigned int p_Character) const;
      float GetLineSpacing() const;

      const Texture& GetTexture() const;
      HM::Rectanglef GetCharacterBounds(unsigned int p_Character) const;

      void MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions);

      bool Load(const std::string& p_Filename, float p_Size, float p_Spacing);
      void Unload();

    private:
      bool m_IsLoaded;
      Texture m_Texture;
      float m_Size;
      float m_Spacing;
  };
}

#endif
