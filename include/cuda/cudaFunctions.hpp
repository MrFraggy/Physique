#pragma once

#ifndef CUDA_FUNCTIONS_HPP
#define CUDA_FUNCTIONS_HPP

#include <vector>
#include <PartyKel/glm.hpp>

void leapFrog(std::vector<bool>& fxd, std::vector<glm::vec3>& p, 
	std::vector<glm::vec3>& v, std::vector<glm::vec3>& f, std::vector<float> mass);

#endif