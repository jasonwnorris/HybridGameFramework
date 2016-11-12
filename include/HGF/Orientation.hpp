// Orientation.hpp

#ifndef __HGF_ORIENTATION_HPP__
#define __HGF_ORIENTATION_HPP__

namespace HGF
{
  enum class Orientation
  {
    None = 1 << 0,
    FlipHorizontal = 1 << 1,
    FlipVertical = 1 << 2,
    FlipBoth = (1 << 1) | (1 << 2)
  };

  inline Orientation operator|(Orientation p_OrientationA, Orientation p_OrientationB)
  {
    return static_cast<Orientation>(static_cast<int>(p_OrientationA) | static_cast<int>(p_OrientationB));
  }

  inline Orientation operator&(Orientation p_OrientationA, Orientation p_OrientationB)
  {
  return static_cast<Orientation>(static_cast<int>(p_OrientationA) & static_cast<int>(p_OrientationB));
  }
}

#endif
