// Effect.cpp

// SDL Includes
#include <SDL2/SDL.h>
// HGF Includes
#include <HGF/Effect.hpp>
// STL Includes
#include <fstream>
#include <string>

namespace HGF
{
  const std::string Effect::PositionColorVertexSource =
#if defined __ANDROID__
    "#version 300 es\n\n"
#else
    "#version 330 core\n\n"
#endif
    "uniform mat4 uProjectionMatrix;\n"
    "uniform mat4 uModelViewMatrix;\n\n"
    "layout(location = 0) in vec2 in_Position;\n"
    "layout(location = 1) in vec4 in_Color;\n\n"
    "out vec4 pass_Color;\n\n"
    "void main()\n"
    "{\n"
    "  pass_Color = in_Color;\n\n"
    "  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(in_Position, 1.0, 1.0);\n"
    "}";

  const std::string Effect::PositionColorFragmentSource =
#if defined __ANDROID__
    "#version 300 es\n\n"
#else
    "#version 330 core\n\n"
#endif
    "in vec4 pass_Color;\n"
    "out vec4 out_Color;\n\n"
    "void main()\n"
    "{\n"
    "  out_Color = pass_Color;\n"
    "}";

  const std::string Effect::PositionColorTextureVertexSource =
#if defined __ANDROID__
    "#version 300 es\n\n"
#else
    "#version 330 core\n\n"
#endif
    "uniform mat4 uProjectionMatrix;\n"
    "uniform mat4 uModelViewMatrix;\n\n"
    "layout(location = 0) in vec2 in_Position;\n"
    "layout(location = 1) in vec4 in_Color;\n"
    "layout(location = 2) in vec2 in_TexCoord;\n\n"
    "out vec4 pass_Color;\n"
    "out vec2 pass_TexCoord;\n\n"
    "void main()\n"
    "{\n"
    "  pass_Color = in_Color;\n"
    "  pass_TexCoord = in_TexCoord;\n\n"
    "  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(in_Position, 1.0, 1.0);\n"
    "}";

  const std::string Effect::PositionColorTextureFragmentSource =
#if defined __ANDROID__
    "#version 300 es\n\n"
#else
    "#version 330 core\n\n"
#endif
    "uniform sampler2D uTextureSampler;\n\n"
    "in vec4 pass_Color;\n"
    "in vec2 pass_TexCoord;\n\n"
    "out vec4 out_Color;\n\n"
    "void main()\n"
    "{\n"
    "  out_Color = texture(uTextureSampler, pass_TexCoord) * pass_Color;\n"
    "}";

  Effect::Effect()
  {
  }

  Effect::~Effect()
  {
    Finalize();
  }

  bool Effect::Create(BasicType p_BasicType)
  {
    if (!Initialize())
    {
      return false;
    }

    switch (p_BasicType)
    {
      case BasicType::PositionColor:
        if (!Attach(PositionColorVertexSource, ShaderType::Vertex) ||
            !Attach(PositionColorFragmentSource, ShaderType::Fragment) ||
            !Link())
        {
          return false;
        }
        return true;
      case BasicType::PositionColorTexture:
        if (!Attach(PositionColorTextureVertexSource, ShaderType::Vertex) ||
            !Attach(PositionColorTextureFragmentSource, ShaderType::Fragment) ||
            !Link())
        {
          return false;
        }
        SetUniform("uTextureSampler", 0);
        return true;
    }

    return false;
  }

  bool Effect::Initialize()
  {
    m_Program = glCreateProgram();

    return true;
  }

  void Effect::Finalize()
  {
    glUseProgram(0);
    glDeleteProgram(m_Program);
  }

  bool Effect::Attach(const std::string& p_Source, ShaderType p_Type)
  {
    const GLchar* source = p_Source.c_str();

    GLint status;
    GLuint shader = glCreateShader(static_cast<int>(p_Type));
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
      GLint length = 0;
      GLchar message[256];
      glGetShaderInfoLog(shader, length, &length, message);

      SDL_Log("[HGF::Effect::Attach] Error compiling shader: %s", message);

      return false;
    }
    else
    {
      glAttachShader(m_Program, shader);
    }

    glDeleteShader(shader);

    return true;
  }

  bool Effect::AttachFromFile(const std::string& p_Filename, ShaderType p_Type)
  {
    std::ifstream file(p_Filename);
    if (file.is_open())
    {
      std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();

      return Attach(buffer, p_Type);
    }

    return false;
  }

  bool Effect::Link()
  {
    GLint linked = GL_FALSE;

    glLinkProgram(m_Program);
    glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
      GLsizei length = 0;
      glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &length);
      GLchar* message = new GLchar[length + 1];
      glGetProgramInfoLog(m_Program, length, &length, message);

      SDL_Log("[HGF::Effect::Link] Shader linking failed: %s", message);
      delete[] message;

      return false;
    }

    // TODO: Make matrix acquisition more dynamic.
    m_ProjectionMatrixLocation = glGetUniformLocation(m_Program, "uProjectionMatrix");
    m_ModelViewMatrixLocation = glGetUniformLocation(m_Program, "uModelViewMatrix");

    return true;
  }

  void Effect::Use()
  {
    glUseProgram(m_Program);
  }

  void Effect::PrintUniforms()
  {
    GLint total;
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &total);
    for (GLint i = 0; i < total; i++)
    {
      int number = 0;
      int length = 0;
      GLenum type = GL_ZERO;
      char name[128];
      glGetActiveUniform(m_Program, i, 127, &length, &number, &type, name);
      name[length] = 0;

      SDL_Log("Uniform #%d: %s", i + 1, name);
    }
  }

  GLint Effect::GetUniform(const std::string& p_Name)
  {
    return glGetUniformLocation(m_Program, p_Name.c_str());
  }

  void Effect::SetProjection(const glm::mat4& p_Matrix)
  {
    glUniformMatrix4fv(m_ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(p_Matrix));
  }

  void Effect::SetModelView(const glm::mat4& p_Matrix)
  {
    glUniformMatrix4fv(m_ModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(p_Matrix));
  }

  void Effect::SetUniform(const std::string& p_Name, int p_Value)
  {
    if (m_Uniforms.find(p_Name) == m_Uniforms.end())
    {
      m_Uniforms[p_Name] = glGetUniformLocation(m_Program, p_Name.c_str());
    }

    glUniform1i(m_Uniforms[p_Name], p_Value);
  }

  void Effect::SetUniform(const std::string& p_Name, float p_Value)
  {
    if (m_Uniforms.find(p_Name) == m_Uniforms.end())
    {
      m_Uniforms[p_Name] = glGetUniformLocation(m_Program, p_Name.c_str());
    }

    glUniform1f(m_Uniforms[p_Name], p_Value);
  }
}
