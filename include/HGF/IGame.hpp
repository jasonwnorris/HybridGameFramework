// IGame.hpp

#ifndef __HGF_IGAME_HPP__
#define __HGF_IGAME_HPP__

// HGF Includes
#include <HGF/SpriteBatch.hpp>
#include <HGF/Timer.hpp>

namespace HGF
{
  class IGame
  {
    public:
      IGame() = default;
      virtual ~IGame() = default;

      bool Run();
      void Quit();

    protected:
      virtual bool Initialize() = 0;
      virtual void Finalize() = 0;

      virtual bool Update(float p_DeltaTime) = 0;
      virtual bool Render(SpriteBatch& p_SpriteBatch) = 0;

    private:
      bool m_IsRunning;
      Timer m_Timer;
      SpriteBatch m_SpriteBatch;
  };
}

#endif
