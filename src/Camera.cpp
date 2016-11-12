// Camera.cpp

// GLM Includes
#include <glm/gtx/transform.hpp>
// HGF Includes
#include <HGF/Camera.hpp>

namespace HGF
{
  const Camera Camera::DefaultCamera;
  const unsigned int Camera::DefaultWidth = 1280;
  const unsigned int Camera::DefaultHeight = 720;

  Camera::Camera()
  {
    m_Position = HM::Vector2f::Zero;
    m_Rotation = 0.0f;
    m_Scale = HM::Vector2f::One;
    m_Width = DefaultWidth;
    m_Height = DefaultHeight;
  }

  Camera::~Camera()
  {
  }

  const HM::Vector2f& Camera::GetPosition() const
  {
    return m_Position;
  }

  float Camera::GetRotation() const
  {
    return m_Rotation;
  }

  const HM::Vector2f& Camera::GetScale() const
  {
    return m_Scale;
  }

  unsigned int Camera::GetWidth() const
  {
    return m_Width;
  }

  unsigned int Camera::GetHeight() const
  {
    return m_Height;
  }

  glm::mat4 Camera::GetProjectionMatrix(ViewType p_View) const
  {
    switch (p_View)
    {
      default:
      case ViewType::Orthographic:
        return glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, 1.0f, -1.0f);
      case ViewType::Perspective:
        return glm::perspective(45.0f, m_Width / (float)m_Height, 0.1f, 1000.0f);
    }
  }

  glm::mat4 Camera::GetModelViewMatrix() const
  {
    glm::mat4 modelViewMatrix;
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(m_Width / 2.0f, m_Height / 2.0f, 0.0f));
    modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(m_Scale.X, m_Scale.Y, 1.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(-m_Position.X, -m_Position.Y, 0.0f));

    return modelViewMatrix;
  }

  void Camera::SetPosition(const HM::Vector2f& p_Position)
  {
    m_Position = p_Position;
  }

  void Camera::SetRotation(float p_Rotation)
  {
    m_Rotation = p_Rotation;
  }

  void Camera::SetScale(const HM::Vector2f& p_Scale)
  {
    m_Scale = p_Scale;
  }

  void Camera::SetTransformation(const HM::Vector2f& p_Position, float p_Rotation, const HM::Vector2f& p_Scale)
  {
    m_Position = p_Position;
    m_Rotation = p_Rotation;
    m_Scale = p_Scale;
  }

  void Camera::SetWidth(unsigned int p_Width)
  {
    m_Width = p_Width;
  }

  void Camera::SetHeight(unsigned int p_Height)
  {
    m_Height = p_Height;
  }

  void Camera::SetDimensions(unsigned int p_Width, unsigned int p_Height)
  {
    m_Width = p_Width;
    m_Height = p_Height;
  }

  void Camera::Translate(const HM::Vector2f& p_Translation)
  {
    m_Position += p_Translation;
  }

  void Camera::Rotate(float p_Rotation)
  {
    m_Rotation += p_Rotation;
  }

  void Camera::Scale(const HM::Vector2f& p_Scale)
  {
    m_Scale += p_Scale;
  }

  void Camera::FromScreenToWorld(const HM::Vector2f& p_ScreenPosition, HM::Vector2f& p_WorldPosition) const
  {
  }

  void Camera::FromWorldToScreen(const HM::Vector2f& p_WorldPosition, HM::Vector2f& p_ScreenPosition) const
  {
  }
}
