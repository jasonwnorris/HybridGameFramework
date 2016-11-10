// Timer.cpp

// HGF Includes
#include <HGF/Timer.hpp>

namespace HGF
{
  Timer::Timer()
  {
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
    {
      SDL_Log("[HGF::Timer] Failed to initialize timer subsystem: %s", SDL_GetError());
    }

    Stop();
  }

  Timer::~Timer()
  {
    SDL_QuitSubSystem(SDL_INIT_TIMER);
  }

  float Timer::GetDeltaTime()
  {
    if (!m_Started || m_Paused)
    {
      return 0.0f;
    }

    Uint32 current = SDL_GetTicks();
    Uint32 difference = current - m_LastTicks;
    m_LastTicks = current;

    return difference / 1000.0f;
  }

  float Timer::GetElapsedTime() const
  {
    return GetTicks() / 1000.0f;
  }

  unsigned long Timer::GetTicks() const
  {
    if (!m_Started)
    {
      return 0;
    }
    else if (m_Paused)
    {
      return m_PausedTicks;
    }

    return SDL_GetTicks() - m_StartTicks;
  }

  void Timer::Start()
  {
    m_StartTicks = SDL_GetTicks();
    m_LastTicks = m_StartTicks;
    m_PausedTicks = 0;
    m_Started = true;
    m_Paused = false;
  }

  void Timer::Stop()
  {
    m_Started = false;
    m_Paused = false;
  }

  void Timer::Pause()
  {
    if (m_Started && !m_Paused)
    {
      m_PausedTicks = SDL_GetTicks() - m_StartTicks;
      m_Paused = true;
    }
  }

  void Timer::Resume()
  {
    if (m_Paused)
    {
      m_StartTicks = SDL_GetTicks() - m_PausedTicks;
      m_PausedTicks = 0;
      m_Paused = false;
    }
  }
}
