#pragma once

#include "vao.h"
#include "vbo.h"
#include "vertex.h"

typedef enum {
	Point,
	Wireframe,
	Full
} DrawMode;

typedef enum {
	Solid,
	AlphaBlending
} RenderMode;

class MeshBuffer {
public:
	MeshBuffer();
	bool load(const VertexBuffer& buffer);
	void draw();
	void setDrawMode(DrawMode m);
	void setRenderMode(RenderMode m);
	bool hasAlphaBlending() const;
	const VertexBuffer& getVertexBuffer() const;
	VertexBuffer& getVertexBuffer();
	void update();

	void setVertexPosition(int i, const glm::vec3& p);

private:
	RenderMode m_renderMode;
	DrawMode m_drawMode;
	VertexBuffer m_buffer;
	VBO m_vbo;
	VBO m_ibo;
	VAO m_vao;
};