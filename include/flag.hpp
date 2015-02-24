#pragma once

#include <graphic/meshbuffer.h>
#include <physic/masses/masse.h>
#include <physic/link.h>

class Masses;
class SpringBreaks;
class Flag {
public:
	Flag(int width, int height, Masses& masses, SpringBreaks& spring);

	/*void update();
	const std::vector<MassePtr>& getMasses();
	const std::vector<LinkPtr>& getLinks();
	void draw();

	void setDrawMode(DrawMode m);*/

protected:
	/*MeshBuffer m_meshBuffer;
	int m_width, m_height;
	std::vector<MassePtr> m_masses;
	std::vector<LinkPtr> m_links;*/
};