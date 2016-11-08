// Color.hpp

#ifndef __HGF_COLOR_HPP__
#define __HGF_COLOR_HPP__

namespace HGF
{
  class Color
  {
    public:
      static const Color White;
      static const Color LightGray;
      static const Color Gray;
      static const Color DarkGray;
      static const Color Black;
      static const Color Red;
      static const Color Green;
      static const Color Blue;
      static const Color Cyan;
      static const Color Magenta;
      static const Color Yellow;
      static const Color Orange;
      static const Color Purple;
      static const Color Maroon;
      static const Color Olive;
      static const Color Navy;
      static const Color TransparentWhite;
      static const Color TransparentBlack;

      Color();
      Color(float p_Red, float p_Green, float p_Blue, float p_Alpha = 1.0f);
      Color(int p_Red, int p_Green, int p_Blue, int p_Alpha = 255);
      Color(const char* p_Hex, float p_Alpha = 1.0f);
      ~Color() = default;

      bool operator==(const Color& p_Color) const;
      bool operator!=(const Color& p_Color) const;
      Color& operator=(const Color& p_Color);
      Color operator+(const Color& p_Color) const;
      Color operator-(const Color& p_Color) const;
      Color operator*(float p_Scalar) const;
      Color operator/(float p_Scalar) const;
      Color& operator+=(const Color& p_Color);
      Color& operator-=(const Color& p_Color);
      Color& operator*=(float p_Scalar);
      Color& operator/=(float p_Scalar);

      float GetRed() const;
      float GetGreen() const;
      float GetBlue() const;
      float GetAlpha() const;

      unsigned char GetRedAsByte() const;
      unsigned char GetGreenAsByte() const;
      unsigned char GetBlueAsByte() const;
      unsigned char GetAlphaAsByte() const;

      void SetRed(float p_Red);
      void SetGreen(float p_Green);
      void SetBlue(float p_Blue);
      void SetAlpha(float p_Alpha);

      void SetRedFromByte(unsigned char p_Red);
      void SetGreenFromByte(unsigned char p_Green);
      void SetBlueFromByte(unsigned char p_Blue);
      void SetAlphaFromByte(unsigned char p_Alpha);

      void Invert(bool p_InvertAlpha = false);
      Color Inverse(bool p_InvertAlpha = false) const;

      static Color Lerp(const Color& p_ColorA, const Color& p_ColorB, float p_Amount);

    private:
      float m_Red;
      float m_Green;
      float m_Blue;
      float m_Alpha;
  };
}

#endif
