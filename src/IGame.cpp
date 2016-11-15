// IGame.cpp

// HGF Includes
#include <HGF/IGame.hpp>

namespace HGF
{
  bool IGame::Run()
  {
    m_IsRunning = true;

    m_Timer.Start();

    if (!m_SpriteBatch.Initialize())
    {
      return false;
    }

    if (!Initialize())
    {
      return false;
    }

    while (m_IsRunning)
    {
      if (!Update(m_Timer.GetDeltaTime()))
      {
        return false;
      }

      if (!Render(m_SpriteBatch))
      {
        return false;
      }
    }

    Finalize();

    m_SpriteBatch.Finalize();

    return true;
  }

  void IGame::Quit()
  {
    m_IsRunning = false;
  }
}
