#include "flag.hpp"
#include "physic/masses/fixe.h"
#include "physic/masses/libre.h"
#include <iostream>

Flag::Flag(int w, int h) : m_width(w), m_height(h) {

	VertexBuffer buffer;

    for (int row = 0; row < m_height; ++row)
    {
    	auto pos = glm::vec3(-m_width/2 * 0.1f, ((m_height / 2) - row) * 0.1f, 0);
		buffer.addVertex({pos, glm::vec3(0,0,0), glm::vec2(0,row*1.f/m_height), glm::vec4(1,1,1,1)});
    	m_masses.push_back(MassePtr(new MasseFixe(pos)));
    }
	for(int col = 1; col<m_width; ++col)
		for(int row = 0; row<m_height; ++row)
		{
			auto pos = glm::vec3(((-m_width/2) + col) * 0.1f, ((m_height / 2) - row)* 0.1f, 0);
			buffer.addVertex({pos, glm::vec3(0,0,0), glm::vec2(col*1.f/m_width,row*1.f/m_height), glm::vec4(1,1,1,1)});
			m_masses.push_back(MassePtr(new MasseLibre(pos, 1.f)));
		}
	for(int col = 0; col < m_width-1; ++col)
    {
        for (int row = 0; row < m_height-1; ++row)
        {
        	uint index1 = col*m_height+row, index2 = col*m_height+row+1;
        	uint index3 = (col+1)*m_height+row+1, index4 = (col+1)*m_height+row;
        	buffer.addTriangle({index1, index2, index3});
        	buffer.addTriangle({index1, index4, index3});
        }
    }
	for(int col = 0; col < 1; ++col)
    {
        for (int row = 0; row < m_height; ++row)
        {
            uint index = col*m_height+row, index2 = (col+1)*m_height+row;
            m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at(index2).get())); // droite
            //std::cout << "link: " << (col) << "," << row << " to " << (col+1) << "," << row << std::endl;
        }
    }
    for(int col = 1; col < m_width; ++col)
    {
        for (int row = 0; row < m_height; ++row)
        {
            uint index = col*m_height+row;
            try {
            if((col+1) < m_width)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at((col+1)*m_height+row).get())); // droite
            if((row+1) < m_height)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at(col*m_height+(row+1)).get())); // bas
            if((col+1) < m_width && (row+1) < m_height)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at((col+1)*m_height+(row+1)).get())); // bas droite
            if((col+1) < m_width && (row-1) >= 0)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at((col+1)*m_height+(row-1)).get())); // haut droite
            if((col+2) < m_width)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at((col+2)*m_height+row).get())); // droite éloigné
            if((row+2) < m_height)
                m_links.push_back(getRessortFrein(m_masses.at(index).get(), m_masses.at(col*m_height+(row+2)).get())); // bas éloigné
            } catch(std::exception& e)
            {
            }
        }
    }

    m_meshBuffer.load(buffer);
    //m_meshBuffer.setDrawMode(DrawMode::Point);
}

void Flag::update() 
{
	auto& buffer = m_meshBuffer.getVertexBuffer();
	for(int x = 0; x<m_width; ++x)
		for(int y = 0; y<m_height; ++y)
		{
			int id = y*m_width+x;
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
	m_meshBuffer.draw();
}

void Flag::setDrawMode(DrawMode m)
{
    m_meshBuffer.setDrawMode(m);
}