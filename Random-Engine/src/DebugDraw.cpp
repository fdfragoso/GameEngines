#if defined(__APPLE_CC__)
#include <OpenGL/gl3.h>
#else
#include <glew/glew.h>
#include <glfw/glfw3.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include "SRE/Debug.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "DebugDraw.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

Camera g_camera;

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	b2Vec2 p1 = vertices[vertexCount - 1];
	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 p2 = vertices[i];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
		p1 = p2;
	}
}
//
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);

	for (int32 i = 1; i < vertexCount - 1; ++i)
	{
		SRE::Debug::drawLine(glm::vec3(vertices[0].x, vertices[0].y, 0), glm::vec3(vertices[i].x, vertices[i].y, 0));
		SRE::Debug::drawLine(glm::vec3(vertices[i].x, vertices[i].y, 0), glm::vec3(vertices[i + 1].x, vertices[i + 1].y, 0));
		SRE::Debug::drawLine(glm::vec3(vertices[i + 1].x, vertices[i + 1].y, 0), glm::vec3(vertices[0].x, vertices[0].y, 0));
	}

	b2Vec2 p1 = vertices[vertexCount - 1];
	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 p2 = vertices[i];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
		p1 = p2;
	}
}
//
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 sinInc = sinf(k_increment);
	float32 cosInc = cosf(k_increment);
	b2Vec2 r1(1.0f, 0.0f);
	b2Vec2 v1 = center + radius * r1;
	for (int32 i = 0; i < k_segments; ++i)
	{
		// Perform rotation to avoid additional trigonometry.
		b2Vec2 r2;
		r2.x = cosInc * r1.x - sinInc * r1.y;
		r2.y = sinInc * r1.x + cosInc * r1.y;
		b2Vec2 v2 = center + radius * r2;
		SRE::Debug::drawLine(glm::vec3(v1.x, v1.y, 0), glm::vec3(v2.x, v2.y, 0));
		r1 = r2;
		v1 = v2;
	}
}
//
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 sinInc = sinf(k_increment);
	float32 cosInc = cosf(k_increment);
	b2Vec2 v0 = center;
	b2Vec2 r1(cosInc, sinInc);
	b2Vec2 v1 = center + radius * r1;
	b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	for (int32 i = 0; i < k_segments; ++i)
	{
		// Perform rotation to avoid additional trigonometry.
		b2Vec2 r2;
		r2.x = cosInc * r1.x - sinInc * r1.y;
		r2.y = sinInc * r1.x + cosInc * r1.y;
		b2Vec2 v2 = center + radius * r2;
		SRE::Debug::drawLine(glm::vec3(v0.x, v0.y, 0), glm::vec3(v1.x, v1.y, 0));
		SRE::Debug::drawLine(glm::vec3(v1.x, v1.y, 0), glm::vec3(v2.x, v2.y, 0));
		SRE::Debug::drawLine(glm::vec3(v2.x, v2.y, 0), glm::vec3(v0.x, v0.y, 0));
		r1 = r2;
		v1 = v2;
	}

	r1.Set(1.0f, 0.0f);
	v1 = center + radius * r1;
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 r2;
		r2.x = cosInc * r1.x - sinInc * r1.y;
		r2.y = sinInc * r1.x + cosInc * r1.y;
		b2Vec2 v2 = center + radius * r2;
		SRE::Debug::drawLine(glm::vec3(v1.x, v1.y, 0), glm::vec3(v2.x, v2.y, 0));
		r1 = r2;
		v1 = v2;
	}

	// Draw a line fixed in the circle to animate rotation.
	b2Vec2 p = center + radius * axis;
	SRE::Debug::drawLine(glm::vec3(center.x, center.y, 0), glm::vec3(p.x, p.y, 0));
}
//
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
}

//
void DebugDraw::DrawTransform(const b2Transform& xf)
{
	const float32 k_axisScale = 0.4f;
	b2Color red(1.0f, 0.0f, 0.0f);
	b2Color green(0.0f, 1.0f, 0.0f);
	b2Vec2 p1 = xf.p, p2;

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
}
void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
}