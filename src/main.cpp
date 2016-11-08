// main.cpp

// HGF Includes
#include <HGF/Window.hpp>

int main(int p_ArgCount, char** p_ArgVars)
{
  HGF::Window window;
  if (!window.Initialize())
  {
    return -1;
  }

  window.PrintInfo();
  window.Clear();
  window.Flip();

  if (!window.Finalize())
  {
    return -1;
  }

  return 0;
}
