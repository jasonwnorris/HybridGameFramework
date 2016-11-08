// WindowAttributes.hpp

#ifndef __HGF_WINDOWATTRIBUTES_HPP__
#define __HGF_WINDOWATTRIBUTES_HPP__

namespace HGF
{
  struct WindowAttributes
  {
    int RedSize = 8;
    int GreenSize = 8;
    int BlueSize = 8;
    int AlphaSize = 8;
    int DepthSize = 32;
    int MultisampleBuffers = 0;
    int MultisampleSamples = 1;
  };
}

#endif
