// SpriteBatch.hpp

#ifndef __HGF_SPRITEBATCH_HPP__
#define __HGF_SPRITEBATCH_HPP__

// HGF Includes
#include <HGF/BlendMode.hpp>
#include <HGF/Camera.hpp>
#include <HGF/Color.hpp>
#include <HGF/Effect.hpp>
#include <HGF/IFont.hpp>
#include <HGF/Orientation.hpp>
#include <HGF/RasterizerState.hpp>
#include <HGF/SortMode.hpp>
#include <HGF/SpriteBatchItem.hpp>
#include <HGF/Texture.hpp>
// HM Includes
#include <HM/Rectangle.hpp>
#include <HM/Vector2.hpp>
// STL Includes
#include <vector>

namespace HGF
{
  class SpriteBatch
  {
    private:
      static const int MaxBatchSize = 1024 * 4;
      static const int MaxVertexCount = MaxBatchSize * 3;
      static const int MaxIndexCount = MaxBatchSize * 3;

    public:
      SpriteBatch();
      ~SpriteBatch();

      int GetDrawCallCount() const;

      bool Initialize();
      void Finalize();

      bool Begin(Effect& p_Effect, const Camera& p_Camera = Camera::DefaultCamera, SortMode p_SortMode = SortMode::None, BlendMode p_BlendMode = BlendMode::None, RasterizerState p_RasterizerState = RasterizerState::CullCounterClockwise);

      bool DrawLine(const HM::Vector2f& p_PositionA, const HM::Vector2f& p_PositionB, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
      bool DrawLine(const HM::Vector2f& p_PositionA, const Color& p_ColorA, const HM::Vector2f& p_PositionB, const Color& p_ColorB, float p_Thickness = 1.0f, float p_Depth = 0.0f);

      bool DrawLines(const std::vector<HM::Vector2f>& p_Positions, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
      bool DrawLines(const std::vector<HM::Vector2f>& p_Positions, const std::vector<Color>& p_Colors, float p_Thickness = 1.0f, float p_Depth = 0.0f);

      bool DrawLineLoop(const std::vector<HM::Vector2f>& p_Positions, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
      bool DrawLineLoop(const std::vector<HM::Vector2f>& p_Positions, const std::vector<Color>& p_Colors, float p_Thickness = 1.0f, float p_Depth = 0.0f);

      bool DrawCircle(const HM::Vector2f& p_Position, const Color& p_Color, float p_Radius, float p_Thickness = 1.0f, float p_Depth = 0.0f);
      bool DrawCircle(const HM::Vector2f& p_Position, const std::vector<Color>& p_Colors, float p_Radius, float p_Thickness = 1.0f, float p_Depth = 0.0f);

      bool DrawSolidTriangle(const HM::Vector2f p_Positions[3], const Color& p_Color, float p_Depth = 0.0f);
      bool DrawSolidTriangle(const HM::Vector2f p_Positions[3], const Color p_Colors[3], float p_Depth = 0.0f);

      bool DrawSolidRectangle(float p_X, float p_Y, float p_Width, float p_Height, const Color& p_Color, float p_Depth = 0.0f);
      bool DrawSolidRectangle(const HM::Rectanglef& p_Rectangle, const Color& p_Color, float p_Depth = 0.0f);
      bool DrawSolidRectangle(const HM::Vector2f& p_Position, const HM::Vector2f& p_Dimensions, const Color& p_Color, float p_Depth = 0.0f);

      bool DrawSolidCircle(const HM::Vector2f& p_Position, const Color& p_Color, float p_Radius, float p_Depth = 0.0f);
      bool DrawSolidCircle(const HM::Vector2f& p_Position, const Color& p_ColorA, const Color& p_ColorB, float p_Radius, float p_Depth = 0.0f);

      bool DrawSprite(const Texture& p_Texture, const HM::Vector2f& p_Position, const HM::Vector2f& p_Dimensions, const HM::Rectanglef& p_SourceRectangle, const Color& p_Color, const HM::Vector2f& p_Origin, float p_Rotation, const HM::Vector2f& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
      bool DrawSprite(const Texture& p_Texture, const HM::Vector2f& p_Position, const HM::Rectanglef& p_DestinationRectangle, const HM::Rectanglef& p_SourceRectangle, const Color& p_Color, const HM::Vector2f& p_Origin, float p_Rotation, const HM::Vector2f& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
      bool DrawSprite(const Texture& p_Texture, const HM::Rectanglef& p_DestinationRectangle, const HM::Rectanglef& p_SourceRectangle, const Color& p_Color, const HM::Vector2f& p_Origin, float p_Rotation, const HM::Vector2f& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
      bool DrawSprite(const Texture& p_Texture, const HM::Vector2f& p_Position, const HM::Rectanglef& p_SourceRectangle, const Color& p_Color, const HM::Vector2f& p_Origin, float p_Rotation, const HM::Vector2f& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);

      bool DrawString(const IFont* const p_Font, const std::string& p_String, const HM::Vector2f& p_Position, const Color& p_Color, float p_Depth = 0.0f);
      bool DrawString(const IFont* const p_Font, const std::string& p_String, const HM::Vector2f& p_Position, const Color& p_Color, const HM::Vector2f& p_Origin, float p_Rotation, const HM::Vector2f& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);

      bool End();

    private:
      void Render();
      void Flush(int p_TextureID, int p_Length);

      SpriteBatchItem& GetNextItem(const Texture& p_Texture, float p_Depth = 0.0f);
      void SetVertexPosition(VertexPositionColorTexture& p_Vertex, float p_X, float p_Y);
      void SetVertexColor(VertexPositionColorTexture& p_Vertex, const Color& p_Color);
      void SetVertexTexCoords(VertexPositionColorTexture& p_Vertex, float p_U, float p_V);
      void SetVertex(VertexPositionColorTexture& p_Vertex, float p_X, float p_Y, const Color& p_Color, float p_U, float p_V);
      void TransformVerticesAbout(SpriteBatchItem& p_Item, const HM::Vector2f& p_Position, float p_CosAngle, float p_SinAngle, Orientation p_Orientation);
      void RotateVerticesAbout(SpriteBatchItem& p_Item, const HM::Vector2f& p_Position, float p_CosAngle, float p_SinAngle);
      void FlipVerticesAbout(SpriteBatchItem& p_Item, const HM::Vector2f& p_Position, Orientation p_Orientation);
      void RotateVertexAbout(VertexPositionColorTexture& p_Vertex, const HM::Vector2f& p_Position, float p_CosAngle, float p_SinAngle);
      void FlipVertexAbout(VertexPositionColorTexture& p_Vertex, const HM::Vector2f& p_Position, Orientation p_Orientation);

      bool m_WithinDrawPair;
      int m_ItemCount;
      int m_FlushCount;
      SortMode m_SortMode;
      BlendMode m_BlendMode;
      RasterizerState m_RasterizerState;
      GLuint m_VertexArrayObject;
      GLuint m_VertexBufferObject;
      GLuint m_IndexBufferObject;
      SpriteBatchItem m_BatchItemList[MaxBatchSize];
      VertexPositionColorTexture m_VertexBuffer[MaxVertexCount];
      Texture m_BlankTexture;
  };
}

#endif
