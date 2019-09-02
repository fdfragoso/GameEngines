
#include "Box2D/Box2D.h"

struct Camera
{
	Camera()
	{
		m_center.Set(0.0f, 20.0f);
		m_extent = 25.0f;
		m_zoom = 1.0f;
		m_width = 1280;
		m_height = 800;
	}

	b2Vec2 ConvertScreenToWorld(const b2Vec2& screenPoint);
	b2Vec2 ConvertWorldToScreen(const b2Vec2& worldPoint);
	void BuildProjectionMatrix(float32* m, float32 zBias);

	b2Vec2 m_center;
	float32 m_extent;
	float32 m_zoom;
	int32 m_width;
	int32 m_height;
};

//! DebugDraw
/*! DebugDraw is our custom class that draws physics debug with SRE */
/*! The structure of the class is based on the correspondent tutorial of Box2D */

class DebugDraw : public b2Draw
{
public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	void DrawTransform(const b2Transform& xf) override;
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
};
extern Camera g_camera;


