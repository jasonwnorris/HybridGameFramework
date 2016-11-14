// GlyphFontStyle.hpp

#ifndef __HGF_GLYPHFONTSTYLE_HPP__
#define __HGF_GLYPHFONTSTYLE_HPP__

// SDL2 Includes
#include <SDL2/SDL_ttf.h>

namespace HGF
{
  enum class GlyphFontStyle : int
  {
    Bold = TTF_STYLE_BOLD,
    Italic = TTF_STYLE_ITALIC,
    Normal = TTF_STYLE_NORMAL,
    Strikethrough = TTF_STYLE_STRIKETHROUGH,
    Underline = TTF_STYLE_UNDERLINE
  };
}

#endif
