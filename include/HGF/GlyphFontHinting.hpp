// GlyphFontHinting.hpp

#ifndef __HGF_GLYPHFONTHINTING_HPP__
#define __HGF_GLYPHFONTHINTING_HPP__

// SDL2 Includes
#include <SDL2/SDL_ttf.h>

namespace HGF
{
  enum class GlyphFontHinting : int
  {
    Light = TTF_HINTING_LIGHT,
    Mono = TTF_HINTING_MONO,
    None = TTF_HINTING_NONE,
    Normal = TTF_HINTING_NORMAL
  };
}

#endif
