// MessageBoxScheme.hpp

#ifndef __HGF_MESSAGEBOXSCHEME_HPP__
#define __HGF_MESSAGEBOXSCHEME_HPP__

// HGF Includes
#include <HGF/Color.hpp>

namespace HGF
{
  struct MessageBoxScheme
  {
    Color BackgroundColor;
    Color TextColor;
    Color ButtonBorderColor;
    Color ButtonBackgroundColor;
    Color ButtonSelectedColor;

    MessageBoxScheme()
    {
      BackgroundColor = Color::Gray;
      TextColor = Color::Black;
      ButtonBorderColor = Color::Black;
      ButtonBackgroundColor = Color::Gray;
      ButtonSelectedColor = Color::LightGray;
    }
  };
}

#endif
