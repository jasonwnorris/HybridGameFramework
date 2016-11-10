// Timer.hpp

#ifndef __HGF_TIMER_HPP__
#define __HGF_TIMER_HPP__

// SDL2 Includes
#include <SDL2/SDL.h>

namespace HGF
{
  class Timer
  {
    public:
      Timer();
      ~Timer();

      float GetDeltaTime();
      float GetElapsedTime() const;
      unsigned long GetTicks() const;

      void Start();
      void Stop();
      void Pause();
      void Resume();

    private:
      Uint32 m_StartTicks;
      Uint32 m_LastTicks;
      Uint32 m_PausedTicks;
      bool m_Started;
      bool m_Paused;
  };
}

#endif
