// IGame.cpp

// HGF Includes
#include <HGF/IGame.hpp>

namespace HGF
{
  bool IGame::Run()
  {
    m_IsRunning = true;

    m_Timer.Start();

    if (!m_Window.Initialize())
    {
      return false;
    }

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
      float deltaTime = m_Timer.GetDeltaTime();

      if (!Update(deltaTime))
      {
        return false;
      }

      m_Window.Clear();

      if (!Render(m_SpriteBatch))
      {
        return false;
      }

      m_Window.Flip();
    }

    Finalize();

    m_SpriteBatch.Finalize();

    m_Window.Finalize();

    return true;
  }

  void IGame::Quit()
  {
    m_IsRunning = false;
  }
}
