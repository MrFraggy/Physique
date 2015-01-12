#include <graphic/meshbuffer.h>
#include <iostream>

MeshBuffer::MeshBuffer() :
	m_renderMode(RenderMode::Solid), m_drawMode(DrawMode::Full)
{
}
bool MeshBuffer::load(const VertexBuffer& buffer) {
	m_buffer = buffer;
	m_vbo.bind();
	glBufferData(GL_ARRAY_BUFFER, m_buffer.getVerticesCount()*sizeof(Vertex3D), m_buffer.getVerticesArray(), GL_STREAM_DRAW);
	m_vbo.unbind();
	m_vao.bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	m_vbo.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, uv));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex3D), (const GLvoid*)offsetof(Vertex3D, color));
	m_vbo.unbind();
	m_vao.unbind();
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_buffer.getTrianglesCount() * sizeof(unsigned int)*3, m_buffer.getTrianglesArray(), GL_STATIC_DRAW);
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);
	return true;
}
void MeshBuffer::draw() {
	m_vao.bind();
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	switch(m_drawMode) {
	case DrawMode::Point:
		glDrawArrays(GL_POINTS, 0, m_buffer.getVerticesCount());
	break;
	case DrawMode::Wireframe:
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glDrawElements(GL_TRIANGLES, m_buffer.getTrianglesCount()*3, GL_UNSIGNED_INT, (void*)0);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
	break;
	case DrawMode::Full:
	default:
		glDrawElements(GL_TRIANGLES, m_buffer.getTrianglesCount()*3, GL_UNSIGNED_INT, (void*)0);
	break;
	}
	m_ibo.unbind(GL_ELEMENT_ARRAY_BUFFER);
	m_vao.unbind();
}
void MeshBuffer::setDrawMode(DrawMode m) {
	m_drawMode = m;
}
void MeshBuffer::setRenderMode(RenderMode m) {
	m_renderMode = m;
}
bool MeshBuffer::hasAlphaBlending() const {
	return m_renderMode == RenderMode::AlphaBlending;
}
const VertexBuffer& MeshBuffer::getVertexBuffer() const {
	return m_buffer;
}
VertexBuffer& MeshBuffer::getVertexBuffer() {
	return m_buffer;
}

void MeshBuffer::update()
{
	m_vbo.bind();
	glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)0, m_buffer.getVerticesCount()*sizeof(Vertex3D), m_buffer.getVerticesArray());
	m_vbo.unbind();
}

void MeshBuffer::setVertexPosition(int i, const glm::vec3& p)
{
	m_buffer.setVertexPosition(i,p);
}