// SpriteFont.cpp

// HGF Includes
#include <HGF/SpriteFont.hpp>
// STL Includes
#include <sstream>
#include <stdio.h>

namespace HGF
{
  SpriteFont::SpriteFont()
  {
  }

  SpriteFont::~SpriteFont()
  {
  }

  float SpriteFont::GetCharacterSpacing(unsigned int p_Character) const
  {
    return m_Options.Spacing;
  }

  float SpriteFont::GetLineSpacing() const
  {
    return m_Options.Size;
  }

  const Texture& SpriteFont::GetTexture() const
  {
    return m_Texture;
  }

  HM::Rectanglef SpriteFont::GetCharacterBounds(unsigned int p_Character) const
  {
    int glyphWidth = m_Texture.GetWidth() / 16;
    int glyphHeight = m_Texture.GetHeight() / 16;

    return HM::Rectanglef((p_Character % 16) * glyphWidth, (p_Character / 16) * glyphHeight, glyphWidth, glyphHeight);
  }

  void SpriteFont::MeasureString(const std::string& p_String, HM::Vector2f& p_Dimensions)
  {
    int lineCount = 0;
    int maxLength = 0;

    std::stringstream ss(p_String);
    std::string line;
    while (std::getline(ss, line))
    {
      int length = static_cast<int>(line.length());
      if (length > maxLength)
      {
        maxLength = length;
      }

      ++lineCount;
    }

    p_Dimensions.X = static_cast<float>(maxLength * m_Texture.GetWidth() / 16);
    p_Dimensions.Y = static_cast<float>(lineCount * m_Texture.GetHeight() / 16);
  }

  bool SpriteFont::Load(const std::string& p_Filename, const SpriteFontOptions& p_Options)
  {
    // Currently only supports textures with 16x16 rendered ASCII-ordered glyphs.
    if (!m_Texture.Load(p_Filename, TextureInterpolation::Nearest, TextureWrapping::ClampToEdge))
    {
      return false;
    }

    m_Options = p_Options;

    return (m_IsLoaded = true);
  }

  void SpriteFont::Unload()
  {
    m_Texture.Unload();

    m_IsLoaded = false;
  }
}
