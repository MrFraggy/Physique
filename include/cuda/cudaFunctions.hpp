#pragma once

#ifndef CUDA_FUNCTIONS_HPP
#define CUDA_FUNCTIONS_HPP

#include <vector>
#include <PartyKel/glm.hpp>

void cudaLeapFrog(std::vector<unsigned char>& fxd, std::vector<glm::vec3>& p, 
std::vector<glm::vec3>& v, std::vector<glm::vec3>& f, std::vector<float> mass);

void cudaConstantForces(std::vector<glm::vec3>& cf);
void cudaSpringbreak(std::vector<int>& mIds, std::vector<float>& blengths);

bool cudaSnapshot(std::vector<glm::vec3>& pos);

#endif