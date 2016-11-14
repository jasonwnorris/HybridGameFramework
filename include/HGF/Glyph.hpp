// Glyph.hpp

#ifndef __HGF_GLYPH_HPP__
#define __HGF_GLYPH_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>

namespace HGF
{
  struct Glyph
  {
    unsigned int Character;
    int Index;
    int MinX;
    int MaxX;
    int MinY;
    int MaxY;
    int Advance;
    int SpacialWidth;
    int SpacialHeight;
    int VisualX;
    int VisualY;
    int VisualWidth;
    int VisualHeight;
    SDL_Surface* Surface;

    bool operator==(const Glyph& p_Other);
  };
}

#endif
