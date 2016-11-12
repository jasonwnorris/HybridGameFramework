// Color.cpp

// SDL2 Includes
#include <SDL2/SDL.h>
// HGF Includes
#include <HGF/Color.hpp>
// HM Includes
#include <HM/Math.hpp>
// STL Includes
#include <string>

namespace HGF
{
  const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
  const Color Color::LightGray = Color(0.75f, 0.75f, 0.75f, 1.0f);
  const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
  const Color Color::DarkGray = Color(0.25f, 0.25f, 0.25f, 1.0f);
  const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
  const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
  const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
  const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
  const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
  const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
  const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
  const Color Color::Orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
  const Color Color::Purple = Color(0.5f, 0.0f, 0.5f, 1.0f);
  const Color Color::Maroon = Color(0.5f, 0.0f, 0.0f, 1.0f);
  const Color Color::Olive = Color(0.0f, 0.5f, 0.0f, 1.0f);
  const Color Color::Navy = Color(0.0f, 0.0f, 0.5f, 1.0f);
  const Color Color::TransparentWhite = Color(1.0f, 1.0f, 1.0f, 0.0f);
  const Color Color::TransparentBlack = Color(0.0f, 0.0f, 0.0f, 0.0f);

  Color::Color()
  {
    m_Red = 1.0f;
    m_Green = 1.0f;
    m_Blue = 1.0f;
    m_Alpha = 1.0f;
  }

  Color::Color(float p_Red, float p_Green, float p_Blue, float p_Alpha)
  {
    SetRed(p_Red);
    SetGreen(p_Green);
    SetBlue(p_Blue);
    SetAlpha(p_Alpha);
  }

  Color::Color(int p_Red, int p_Green, int p_Blue, int p_Alpha)
  {
    SetRedFromByte(p_Red);
    SetGreenFromByte(p_Green);
    SetBlueFromByte(p_Blue);
    SetAlphaFromByte(p_Alpha);
  }

  Color::Color(const char* p_Hex, float p_Alpha)
  {
    int value = std::stoi(p_Hex, 0, 16);

    m_Red = ((value >> 16) & 0xFF) / 255.0f;
    m_Green = ((value >> 8) & 0xFF) / 255.0f;;
    m_Blue = (value & 0xFF) / 255.0f;;
    m_Alpha = p_Alpha;
  }

  bool Color::operator==(const Color& p_Color) const
  {
    return m_Red == p_Color.GetRed() && m_Green == p_Color.GetGreen() && m_Blue == p_Color.GetBlue() && m_Alpha == p_Color.GetAlpha();
  }

  bool Color::operator!=(const Color& p_Color) const
  {
    return m_Red != p_Color.GetRed() || m_Green != p_Color.GetGreen() || m_Blue != p_Color.GetBlue() || m_Alpha != p_Color.GetAlpha();
  }

  Color& Color::operator=(const Color& p_Color)
  {
    m_Red = p_Color.GetRed();
    m_Green = p_Color.GetGreen();
    m_Blue = p_Color.GetBlue();
    m_Alpha = p_Color.GetAlpha();

    return *this;
  }

  Color Color::operator+(const Color& p_Color) const
  {
    return Color(m_Red + p_Color.GetRed(), m_Green + p_Color.GetGreen(), m_Blue + p_Color.GetBlue(), m_Alpha);
  }

  Color Color::operator-(const Color& p_Color) const
  {
    return Color(m_Red - p_Color.GetRed(), m_Green - p_Color.GetGreen(), m_Blue - p_Color.GetBlue(), m_Alpha);
  }

  Color Color::operator*(float p_Scalar) const
  {
    return Color(m_Red * p_Scalar, m_Green * p_Scalar, m_Blue * p_Scalar, m_Alpha);
  }

  Color Color::operator/(float p_Scalar) const
  {
    if (p_Scalar != 0.0f)
    {
      return Color(m_Red / p_Scalar, m_Green / p_Scalar, m_Blue / p_Scalar, m_Alpha);
    }

    return Color::White;
  }

  Color& Color::operator+=(const Color& p_Color)
  {
    m_Red += p_Color.GetRed();
    m_Green += p_Color.GetGreen();
    m_Blue += p_Color.GetBlue();

    return *this;
  }

  Color& Color::operator-=(const Color& p_Color)
  {
    m_Red -= p_Color.GetRed();
    m_Green -= p_Color.GetGreen();
    m_Blue -= p_Color.GetBlue();

    return *this;
  }

  Color& Color::operator*=(float p_Scalar)
  {
    m_Red *= p_Scalar;
    m_Green *= p_Scalar;
    m_Blue *= p_Scalar;

    return *this;
  }

  Color& Color::operator/=(float p_Scalar)
  {
    if (p_Scalar != 0.0f)
    {
      m_Red /= p_Scalar;
      m_Green /= p_Scalar;
      m_Blue /= p_Scalar;
    }

    return *this;
  }

  float Color::GetRed() const
  {
    return m_Red;
  }

  float Color::GetGreen() const
  {
    return m_Green;
  }

  float Color::GetBlue() const
  {
    return m_Blue;
  }

  float Color::GetAlpha() const
  {
    return m_Alpha;
  }

  unsigned char Color::GetRedAsByte() const
  {
    return static_cast<unsigned char>(GetRed() * 255);
  }

  unsigned char Color::GetGreenAsByte() const
  {
    return static_cast<unsigned char>(GetGreen() * 255);
  }

  unsigned char Color::GetBlueAsByte() const
  {
    return static_cast<unsigned char>(GetBlue() * 255);
  }

  unsigned char Color::GetAlphaAsByte() const
  {
    return static_cast<unsigned char>(GetAlpha() * 255);
  }

  unsigned int Color::GetAsComposite() const
  {
    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    Uint32 color = SDL_MapRGBA(format,
                               static_cast<unsigned char>(GetRedAsByte()),
                               static_cast<unsigned char>(GetGreenAsByte()),
                               static_cast<unsigned char>(GetBlueAsByte()),
                               static_cast<unsigned char>(GetAlphaAsByte()));

    SDL_FreeFormat(format);

    return static_cast<unsigned int>(color);
  }

  void Color::SetRed(float p_Red)
  {
    m_Red = p_Red;
  }

  void Color::SetGreen(float p_Green)
  {
    m_Green = p_Green;
  }

  void Color::SetBlue(float p_Blue)
  {
    m_Blue = p_Blue;
  }

  void Color::SetAlpha(float p_Alpha)
  {
    m_Alpha = p_Alpha;
  }

  void Color::SetRedFromByte(unsigned char p_Red)
  {
    m_Red = p_Red / 255.0f;
  }

  void Color::SetGreenFromByte(unsigned char p_Green)
  {
    m_Green = p_Green / 255.0f;
  }

  void Color::SetBlueFromByte(unsigned char p_Blue)
  {
    m_Blue = p_Blue / 255.0f;
  }

  void Color::SetAlphaFromByte(unsigned char p_Alpha)
  {
    m_Alpha = p_Alpha / 255.0f;
  }

  void Color::SetFromComposite(Uint32 p_Color)
  {
    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
    SDL_GetRGBA(p_Color, format, &red, &green, &blue, &alpha);

    SDL_FreeFormat(format);

    SetRedFromByte(static_cast<unsigned char>(red));
    SetGreenFromByte(static_cast<unsigned char>(green));
    SetBlueFromByte(static_cast<unsigned char>(blue));
    SetAlphaFromByte(static_cast<unsigned char>(alpha));
  }

  void Color::Invert(bool p_InvertAlpha)
  {
    m_Red = 1.0f - m_Red;
    m_Green = 1.0f - m_Green;
    m_Blue = 1.0f - m_Blue;
    m_Alpha = p_InvertAlpha ? 1.0f - m_Alpha : m_Alpha;
  }

  Color Color::Inverse(bool p_InvertAlpha) const
  {
    return Color(1.0f - m_Red, 1.0f - m_Green, 1.0f - m_Blue, p_InvertAlpha ? 1.0f - m_Alpha : m_Alpha);
  }

  Color Color::Lerp(const Color& p_ColorA, const Color& p_ColorB, float p_Amount)
  {
    return Color(HM::Math::Lerp(p_ColorA.GetRed(), p_ColorB.GetRed(), p_Amount),
                 HM::Math::Lerp(p_ColorA.GetGreen(), p_ColorB.GetGreen(), p_Amount),
                 HM::Math::Lerp(p_ColorA.GetBlue(), p_ColorB.GetBlue(), p_Amount),
                 HM::Math::Lerp(p_ColorA.GetAlpha(), p_ColorB.GetAlpha(), p_Amount));
  }
}
