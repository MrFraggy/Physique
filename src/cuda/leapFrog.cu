#include "cuda/cudaFunctions.hpp"

#include "leapFrogKernel.icu"

bool* d_Fixd = NULL;
glm::vec3* d_Pos = NULL;
glm::vec3* d_Vel = NULL;
glm::vec3* d_Frc = NULL;
float* d_Mass = NULL;

void leapFrog(std::vector<bool>& fxd, std::vector<glm::vec3>& p, 
	std::vector<glm::vec3>& v, std::vector<glm::vec3>& f, std::vector<float> mass) 
{
	int size = fxd.size();
	if(d_Fixd == NULL)
	{
		//cudaMalloc((void**) &d_Fixd, sizeof(bool)*size);
		//cudaMemcpy(d_Fixd, fxd.data(), sizeof(bool)*size, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Pos, sizeof(glm::vec3)*size);
		cudaMemcpy(d_Pos, p.data(), sizeof(glm::vec3)*size, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Vel, sizeof(glm::vec3)*size);
		cudaMemcpy(d_Vel, v.data(), sizeof(glm::vec3)*size, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Frc, sizeof(glm::vec3)*size);
		cudaMemcpy(d_Frc, f.data(), sizeof(glm::vec3)*size, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Mass, sizeof(float)*size);
		cudaMemcpy(d_Mass, mass.data(), sizeof(float)*size, cudaMemcpyHostToDevice);
	}

	dim3  grid( 1, 1, 1);
	dim3  threads( 128, 1, 1);

	// execute the kernel
	leapFrogKernel<<< grid, threads>>>(d_Fixd, d_Pos, d_Vel, d_Frc, d_Mass, size);
	//cudaMemcpy(fxd.data(), d_Fixd, sizeof(bool)*size, cudaMemcpyDeviceToHost);
	cudaMemcpy(p.data(), d_Pos, sizeof(glm::vec3)*size, cudaMemcpyDeviceToHost);
	cudaMemcpy(v.data(), d_Vel, sizeof(glm::vec3)*size, cudaMemcpyDeviceToHost);
	cudaMemcpy(f.data(), d_Frc, sizeof(glm::vec3)*size, cudaMemcpyDeviceToHost);
	cudaMemcpy(mass.data(), d_Mass, sizeof(float)*size, cudaMemcpyDeviceToHost);
}