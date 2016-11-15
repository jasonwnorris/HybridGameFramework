// IGame.hpp

#ifndef __HGF_IGAME_HPP__
#define __HGF_IGAME_HPP__

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

      virtual bool Update() = 0;
      virtual bool Render() = 0;

    private:
      bool m_IsRunning;
  };
}

#endif
