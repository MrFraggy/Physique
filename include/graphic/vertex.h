#pragma once

#include <PartyKel/glm.hpp>
#include <vector>

struct Vertex3D {
	glm::vec3 position, normal;
	glm::vec2 uv;
	glm::vec3 color;
	Vertex3D(const glm::vec3& p, const glm::vec3& n, const glm::vec2& u, const glm::vec4& c) :
		position(p), normal(n), uv(u), color(c) {}

	void setPosition(const glm::vec3& p)
	{
		position = p;
	}
};

struct Triangle {
	unsigned int p,p2,p3;
};

class VertexBuffer {
public:
	void addVertex(const Vertex3D& v) {
		vertices.push_back(v);
	}
	void addTriangle(const Triangle& t) {
		triangles.push_back(t);
	}

	void setVertexPosition(int i, const glm::vec3& p)  {
		vertices[i].setPosition(p);
	}

	Vertex3D* getVerticesArray() {
		return vertices.data();
	}

	Triangle* getTrianglesArray() {
		return triangles.data();
	}

	unsigned int getVerticesCount() {
		return vertices.size();
	}

	unsigned int getTrianglesCount() {
		return triangles.size();
	}

	Vertex3D& getVertex(unsigned int i) { return vertices[i]; }

protected:
	std::vector<Vertex3D> vertices;
	std::vector<Triangle> triangles;
};