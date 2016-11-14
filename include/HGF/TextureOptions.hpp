// TextureOptions.hpp

#ifndef __HGF_TEXTUREOPTIONS_HPP__
#define __HGF_TEXTUREOPTIONS_HPP__

// HGF Includes
#include <HGF/TextureInterpolation.hpp>
#include <HGF/TextureWrapping.hpp>

namespace HGF
{
  struct TextureOptions
  {
    TextureInterpolation Interpolation;
    TextureWrapping Wrapping;
  };
}

#endif
