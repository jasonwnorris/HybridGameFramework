// ShaderType.hpp

#ifndef __HGF_SHADERTYPE_HPP___
#define __HGF_SHADERTYPE_HPP___

// OpenGL Includes
#ifdef __APPLE__
  #include <OpenGL/gl3.h>
  #include <OpenGL/gl3ext.h>
#else
  #include <GL/glew.h>
#endif

namespace HGF
{
  enum class ShaderType
  {
    Fragment = GL_FRAGMENT_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Vertex = GL_VERTEX_SHADER
  };
}

#endif
