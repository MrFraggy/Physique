#pragma once

#include <functional>
#include <vector>

typedef std::function<void(bool, glm::vec3&, glm::vec3&, glm::vec3&)> MassUpdateFunction;

class Masses {
public:
	int create(const glm::vec3& pos, float mass, bool fix = false, float rad = 1.f, const glm::vec3& color = glm::vec3(0,1,0))
	{
		int id = positions.size();
		positions.push_back(pos);
		velocities.push_back(glm::vec3(0,0,0));
		forces.push_back(glm::vec3(0,0,0));
		colors.push_back(color);
		masses.push_back(mass);
		radius.push_back(rad);
		fixed.push_back(fix);
		return id;
	}

	void update() 
	{
		for(unsigned int i = 0; i<positions.size(); ++i)
			updateFunc(fixed[i], positions[i], velocities[i], forces[i]);
	}

	void setUpdateFunction(MassUpdateFunction u) { updateFunc = u; }

protected:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	std::vector<glm::vec3> forces;
	std::vector<glm::vec3> colors;
	std::vector<float> masses;
	std::vector<float> radius;
	std::vector<bool> fixed;

	MassUpdateFunction updateFunc;
};