#include "flag.hpp"
#include "physic/masses/fixe.h"
#include "physic/masses/libre.h"
#include "physic/masses/masses.h"
#include "physic/springbreaks.h"
#include <iostream>

Flag::Flag(int w, int h, Masses& masses, SpringBreaks& spring)// : w(w), h(h)
{

	//VertexBuffer buffer;
    //auto& masses = Masses::get();
    int baseId = masses.getCount();
    float length = 0.1f;

    for (int row = 0; row < h; ++row)
    {
    	auto pos = glm::vec3(-w/2 * 0.1f, ((h / 2) - row) * 0.1f, 0);
		//buffer.addVertex({pos, glm::vec3(0,0,0), glm::vec2(0,row*1.f/h), glm::vec4(1,1,1,1)});
    	masses.create(pos, 1, true,1.f, glm::vec3(1,0,0));
        //m_masses.push_back(MassePtr(new MasseFixe(pos)));
    }
	for(int col = 1; col<w; ++col)
		for(int row = 0; row<h; ++row)
		{
			auto pos = glm::vec3(((-w/2) + col) * 0.1f, ((h / 2) - row)* 0.1f, 0);
			//buffer.addVertex({pos, glm::vec3(0,0,0), glm::vec2(col*1.f/w,row*1.f/h), glm::vec4(1,1,1,1)});
			//m_masses.push_back(MassePtr(new MasseLibre(pos, 1.f)));
            masses.create(pos, 1, false);
		}
	/*for(int col = 0; col < w-1; ++col)
    {
        for (int row = 0; row < h-1; ++row)
        {
        	uint index1 = col*h+row, index2 = col*h+row+1;
        	uint index3 = (col+1)*h+row+1, index4 = (col+1)*h+row;
        	//buffer.addTriangle({index1, index2, index3});
        	//buffer.addTriangle({index1, index4, index3});
        }
    }*/
	for(int col = 0; col < 1; ++col)
    {
        for (int row = 0; row < h; ++row)
        {
            uint index = col*h+row, index2 = (col+1)*h+row;
            spring.create(baseId+index, baseId+index2, 0.1f);
            //m_links.push_back(createRessortFrein(m_masses.at(index).get(), m_masses.at(index2).get())); // droite
            //std::cout << "link: " << (col) << "," << row << " to " << (col+1) << "," << row << std::endl;
        }
    }

    auto& position = masses.getPositions();
    for(int col = 1; col < w; ++col)
    {
        for (int row = 0; row < h; ++row)
        {
            uint index = col*h+row;
            try {
                int id1 = baseId+index;
            if((col+1) < w)
                spring.create(id1, baseId+(col+1)*h+row, glm::length(position[id1]-position[baseId+(col+1)*h+row]));
            if((row+1) < h)
                spring.create(id1, baseId+col*h+(row+1), glm::length(position[id1]-position[baseId+col*h+(row+1)]));
            if((col+1) < w && (row+1) < h)
                spring.create(id1, baseId+(col+1)*h+(row+1), glm::length(position[id1]-position[baseId+(col+1)*h+(row+1)]));
            if((col+1) < w && (row-1) >= 0)
                spring.create(id1, baseId+(col+1)*h+(row-1), glm::length(position[id1]-position[baseId+(col+1)*h+(row-1)]));
            if((col+2) < w)
                spring.create(id1, baseId+(col+2)*h+row, glm::length(position[id1]-position[baseId+(col+2)*h+row]));
            if((row+2) < h)
                spring.create(id1, baseId+col*h+(row+2), glm::length(position[id1]-position[baseId+col*h+(row+2)]));
            } catch(std::exception& e)
            {
            }
        }
    }

    //m_meshBuffer.load(buffer);
    //m_meshBuffer.setDrawMode(DrawMode::Point);
}
/*
void Flag::update() 
{
	auto& buffer = m_meshBuffer.getVertexBuffer();
	for(int x = 0; x<w; ++x)
		for(int y = 0; y<h; ++y)
		{
			int id = y*w+x;
			buffer.setVertexPosition(id, m_masses[id]->getPosition());
		}

	m_meshBuffer.update();
}

const std::vector<MassePtr>& Flag::getMasses() 
{
	return m_masses;
}

const std::vector<LinkPtr>& Flag::getLinks()
{
	return m_links;
}

void Flag::draw()
{
	//m_meshBuffer.draw();
}

void Flag::setDrawMode(DrawMode m)
{
    //m_meshBuffer.setDrawMode(m);
}*/