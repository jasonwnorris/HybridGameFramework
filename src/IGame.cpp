// IGame.cpp

// HGF Includes
#include <HGF/IGame.hpp>

namespace HGF
{
  bool IGame::Run()
  {
    m_IsRunning = true;

    if (!Initialize())
    {
      return false;
    }

    while (m_IsRunning)
    {
      if (!Update())
      {
        return false;
      }

      if (!Render())
      {
        return false;
      }
    }

    Finalize();

    return true;
  }

  void IGame::Quit()
  {
    m_IsRunning = false;
  }
}
