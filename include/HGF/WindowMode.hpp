// WindowMode.hpp

#ifndef __HGF_WINDOWMODE_HPP__
#define __HGF_WINDOWMODE_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>

namespace HGF
{
  enum class WindowMode
  {
    Windowed = SDL_WINDOW_SHOWN,
    BorderlessWindowed = SDL_WINDOW_BORDERLESS,
    Fullscreen = SDL_WINDOW_FULLSCREEN,
    FullscreenWindowed = SDL_WINDOW_FULLSCREEN_DESKTOP
  };
}

#endif
