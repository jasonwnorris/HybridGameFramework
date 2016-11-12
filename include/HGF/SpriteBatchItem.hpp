// SpriteBatchItem.hpp

#ifndef __HGF_SPRITEBATCHITEM_HPP___
#define __HGF_SPRITEBATCHITEM_HPP___

// HGF Includes
#include <HGF/VertexDefinitions.hpp>

namespace HGF
{
  struct SpriteBatchItem
  {
    unsigned int TextureID;
    float Depth;
    VertexPositionColorTexture VertexA;
    VertexPositionColorTexture VertexB;
    VertexPositionColorTexture VertexC;
  };
}

#endif
