// GlyphFontOptions.hpp

#ifndef __HGF_GLYPHFONTOPTIONS_HPP__
#define __HGF_GLYPHFONTOPTIONS_HPP__

// HGF Includes
#include <HGF/GlyphFontHinting.hpp>
#include <HGF/GlyphFontStyle.hpp>

namespace HGF
{
  struct GlyphFontOptions
  {
    int Size = 0;
    GlyphFontStyle Style = GlyphFontStyle::Normal;
    GlyphFontHinting Hinting = GlyphFontHinting::None;
    int Outline = 0;
    bool UseKerning = true;
  };
}

#endif
