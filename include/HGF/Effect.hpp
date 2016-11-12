// Effect.hpp

#ifndef __HGF_EFFECT_HPP__
#define __HGF_EFFECT_HPP__

// GL Includes
#include <GL/glew.h>
// GLM Includes
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// HGF Includes
#include <HGF/BasicType.hpp>
#include <HGF/ShaderType.hpp>
// STL Includes
#include <map>
#include <string>

namespace HGF
{
  class Effect
  {
    public:
      Effect();
      ~Effect();

      bool Create(BasicType p_BasicType);

      bool Initialize();
      void Finalize();

      bool Attach(const std::string& p_Source, ShaderType p_Type);
      bool AttachFromFile(const std::string& p_Filename, ShaderType p_Type);
      bool Link();
      void Use();
      void PrintUniforms();

      GLint GetUniform(const std::string& p_Name);

      void SetProjection(const glm::mat4& p_Matrix);
      void SetModelView(const glm::mat4& p_Matrix);
      void SetUniform(const std::string& p_Name, int p_Value);
      void SetUniform(const std::string& p_Name, float p_Value);

    private:
      static const std::string PositionColorVertexSource;
      static const std::string PositionColorFragmentSource;
      static const std::string PositionColorTextureVertexSource;
      static const std::string PositionColorTextureFragmentSource;

      GLuint m_Program;
      GLint m_ProjectionMatrixLocation;
      GLint m_ModelViewMatrixLocation;
      std::map<std::string, GLint> m_Uniforms;
  };
}

#endif
