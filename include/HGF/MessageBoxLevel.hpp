// MessageBoxLevel.hpp

#ifndef __HGF_MESSAGEBOXLEVEL_HPP__
#define __HGF_MESSAGEBOXLEVEL_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>

namespace HGF
{
  enum class MessageBoxLevel
  {
    Information = SDL_MESSAGEBOX_INFORMATION,
    Warning = SDL_MESSAGEBOX_WARNING,
    Error = SDL_MESSAGEBOX_ERROR
  };
}

#endif
