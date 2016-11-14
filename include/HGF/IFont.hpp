// IFont.hpp

#ifndef __HGF_IFONT_HPP__
#define __HGF_IFONT_HPP__

// HGF Includes
#include <HGF/Texture.hpp>
// HM Includes
#include <HM/Rectangle.hpp>
#include <HM/Vector2.hpp>

namespace HGF
{
  class IFont
  {
    public:
      IFont() = default;
      virtual ~IFont() = default;

      virtual float GetCharacterSpacing(unsigned int p_Character) const = 0;
      virtual float GetLineSpacing() const = 0;

      virtual const Texture& GetTexture() const = 0;
      virtual HM::Rectanglef GetCharacterBounds(unsigned int p_Character) const = 0;

      virtual void MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions) = 0;
  };
}

#endif
