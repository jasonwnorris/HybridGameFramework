// Camera.hpp

#ifndef __HGF_CAMERA_HPP__
#define __HGF_CAMERA_HPP__

// GLM Includes
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
// HGF Includes
#include <HGF/ViewType.hpp>
// HM Includes
#include <HM/Vector2.hpp>

namespace HGF
{
  class Camera
  {
    public:
      Camera();
      ~Camera();

      static const Camera DefaultCamera;

      const HM::Vector2f& GetPosition() const;
      float GetRotation() const;
      const HM::Vector2f& GetScale() const;
      unsigned int GetWidth() const;
      unsigned int GetHeight() const;
      glm::mat4 GetProjectionMatrix(ViewType p_View = ViewType::Orthographic) const;
      glm::mat4 GetModelViewMatrix() const;

      void SetPosition(const HM::Vector2f& p_Position);
      void SetRotation(float p_Rotation);
      void SetScale(const HM::Vector2f& p_Scale);
      void SetTransformation(const HM::Vector2f& p_Position, float p_Rotation, const HM::Vector2f& p_Scale);
      void SetWidth(unsigned int p_Width);
      void SetHeight(unsigned int p_Height);
      void SetDimensions(unsigned int p_Width, unsigned int p_Height);

      void Translate(const HM::Vector2f& p_Translation);
      void Rotate(float p_Rotation);
      void Scale(const HM::Vector2f& p_Scale);

      void FromScreenToWorld(const HM::Vector2f& p_ScreenPosition, HM::Vector2f& p_WorldPosition) const;
      void FromWorldToScreen(const HM::Vector2f& p_WorldPosition, HM::Vector2f& p_ScreenPosition) const;

    private:
      static const unsigned int DefaultWidth;
      static const unsigned int DefaultHeight;
      static const glm::vec3 ForwardAxis;

      HM::Vector2f m_Position;
      float m_Rotation;
      HM::Vector2f m_Scale;
      unsigned int m_Width;
      float m_HalfWidth;
      unsigned int m_Height;
      float m_HalfHeight;
  };
}

#endif
