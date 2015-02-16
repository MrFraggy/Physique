#pragma once

class ConstantForces {
public:
	ConstantForces(Masses& masses) : masses(masses) {}

	int create(const glm::vec3& f)
	{
		int id = constantForces.size();
		constantForces.push_back(f);
		return id;
	}

	void update()
	{
		auto& forces = masses.getForces();
		for(int i = 0; i<forces.size(); ++i)
		{
			for(int j = 0; j<constantForces.size(); ++j)
				forces[i] += constantForces[j];
		}
	}

protected:
	Masses& masses;
	std::vector<glm::vec3> constantForces;

};