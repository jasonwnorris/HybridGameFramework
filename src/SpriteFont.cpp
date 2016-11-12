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
    m_IsLoaded = false;
  }

  SpriteFont::~SpriteFont()
  {
    if (m_IsLoaded)
    {
      Unload();
    }
  }

  float SpriteFont::GetCharacterSpacing(unsigned int p_Character) const
  {
    return m_Spacing;
  }

  float SpriteFont::GetLineSpacing() const
  {
    return m_Size;
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

  bool SpriteFont::Load(const std::string& p_Filename, float p_Size, float p_Spacing)
  {
    // Currently only supports textures with 16x16 rendered ASCII-ordered glyphs.
    if (!m_Texture.Load(p_Filename, TextureInterpolation::Nearest, TextureWrapping::ClampToEdge))
    {
      return false;
    }

    m_Size = p_Size;
    m_Spacing = p_Spacing;

    return (m_IsLoaded = true);
  }

  void SpriteFont::Unload()
  {
    if (!m_IsLoaded)
    {
      SDL_Log("[HGF::SpriteFont::Unload] SpriteFont already unloaded. Doing nothing.");
    }
    else
    {
      m_Texture.Unload();

      m_IsLoaded = false;
    }
  }
}
