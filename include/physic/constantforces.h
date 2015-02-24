#pragma once

class ConstantForces {
public:
	ConstantForces(Masses& masses) : masses(masses) {}

	int create(const glm::vec3& f, const glm::vec3& d = glm::vec3(0,0,0))
	{
		int id = constantForces.size();
		constantForces.push_back(f);
		deviationForces.push_back(d);
		return id;
	}

	void update()
	{
		auto& forces = masses.getForces();
		for(int j = 0; j<constantForces.size(); ++j) {
			auto tmp = deviationForces[j];
			auto deviation = glm::linearRand(-tmp,tmp);
			for(int i = 0; i<forces.size(); ++i)
			{
				forces[i] += constantForces[j]+deviation;
			}
		}
	}

protected:
	Masses& masses;
	std::vector<glm::vec3> constantForces;
	std::vector<glm::vec3> deviationForces;

};