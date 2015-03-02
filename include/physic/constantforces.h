#pragma once

#include <cuda/cudaFunctions.hpp>

class ConstantForces {
public:
	ConstantForces(Masses& masses) : masses(masses) {}

	int create(const glm::vec3& direction, const glm::vec3& deviation = glm::vec3(0,0,0))
	{
		int id = constantForces.size();
		constantForces.push_back(direction);
		deviationForces.push_back(deviation);
		return id;
	}

	void update()
	{
		cudaConstantForces(constantForces, deviationForces);
		/*auto& forces = masses.getForces();
		for(int j = 0; j<constantForces.size(); ++j) {
			auto tmp = deviationForces[j];
			auto deviation = glm::linearRand(-tmp,tmp);
			for(int i = 0; i<forces.size(); ++i)
			{
				forces[i] += constantForces[j]+deviation;
			}
		}*/
	}

protected:
	Masses& masses;
	std::vector<glm::vec3> constantForces;
	std::vector<glm::vec3> deviationForces;
};