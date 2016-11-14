// Glyph.cpp

// HGF Includes
#include <HGF/Glyph.hpp>

namespace HGF
{
  bool Glyph::operator==(const Glyph& p_Other)
  {
    return Character == p_Other.Character && Index == p_Other.Index;
  }
}
