#include "cuda/cudaFunctions.hpp"

#include "leapFrog.ker"
#include "constantForces.ker"
#include "springBreak.ker"
#include "autoCollide.ker"

#include <iostream>
#include <ctime>

unsigned int d_MSize = 0;
// Masses
bool* d_Fixd = NULL;
glm::vec3* d_Pos = NULL;
glm::vec3* d_Vel = NULL;
glm::vec3* d_Frc = NULL;
float* d_Mass = NULL;

// Constant forces
unsigned int d_CstSize = 0;
glm::vec3* d_CstFrc = NULL;
glm::vec3* d_DevFrc = NULL;

// Spring breaks
int* d_MIds = NULL;
float* d_BLengths = NULL;
unsigned int d_MCount = 0;

void cudaLeapFrog(std::vector<unsigned char>& fxd, std::vector<glm::vec3>& p, 
	std::vector<glm::vec3>& v, std::vector<glm::vec3>& f, std::vector<float> mass) 
{
	
	if(d_Fixd == NULL)
	{
		d_MSize = fxd.size();

		cudaMalloc((void**) &d_Fixd, sizeof(unsigned char)*d_MSize);
		cudaMemcpy(d_Fixd, fxd.data(), sizeof(unsigned char)*d_MSize, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Pos, sizeof(glm::vec3)*d_MSize);
		cudaMemcpy(d_Pos, p.data(), sizeof(glm::vec3)*d_MSize, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Vel, sizeof(glm::vec3)*d_MSize);
		cudaMemcpy(d_Vel, v.data(), sizeof(glm::vec3)*d_MSize, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Frc, sizeof(glm::vec3)*d_MSize);
		cudaMemcpy(d_Frc, f.data(), sizeof(glm::vec3)*d_MSize, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_Mass, sizeof(float)*d_MSize);
		cudaMemcpy(d_Mass, mass.data(), sizeof(float)*d_MSize, cudaMemcpyHostToDevice);
	}

	dim3  grid( 5, 5, 1);
	dim3  threads( 5, 5, 1);

	// execute the kernel
	leapFrogKernel<<< grid, threads>>>(d_Fixd, d_Pos, d_Vel, d_Frc, d_Mass, d_MSize);
	
	/*cudaMemcpy(fxd.data(), d_Fixd, sizeof(unsigned char)*d_MSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(p.data(), d_Pos, sizeof(glm::vec3)*d_MSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(v.data(), d_Vel, sizeof(glm::vec3)*d_MSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(f.data(), d_Frc, sizeof(glm::vec3)*d_MSize, cudaMemcpyDeviceToHost);
	cudaMemcpy(mass.data(), d_Mass, sizeof(float)*d_MSize, cudaMemcpyDeviceToHost);*/
}

void cudaConstantForces(std::vector<glm::vec3>& cf, std::vector<glm::vec3>& df)
{
	if(d_Pos == NULL)
	{
		return;
	}

	if(d_CstFrc == NULL)
	{
		d_CstSize = cf.size();
		cudaMalloc((void**) &d_CstFrc, sizeof(glm::vec3)*d_CstSize);
		cudaMemcpy(d_CstFrc, cf.data(), sizeof(glm::vec3)*d_CstSize, cudaMemcpyHostToDevice);
		cudaMalloc((void**) &d_DevFrc, sizeof(glm::vec3)*d_CstSize);
		cudaMemcpy(d_DevFrc, df.data(), sizeof(glm::vec3)*d_CstSize, cudaMemcpyHostToDevice);
	}
	glm::vec3 intensity = glm::linearRand(glm::vec3(-1,-1,-1),glm::vec3(1,1,1));
	dim3  grid( 5, 5, 1);
	dim3  threads( 5, 5, 1);

	// execute the kernel
	constantForcesKernel<<< grid, threads>>>(d_Frc, d_CstFrc, d_DevFrc, d_MSize, d_CstSize, intensity);
}

void cudaSpringbreak(std::vector<int>& mIds, std::vector<float>& blengths)
{
	if(d_Pos == NULL)
		return;

	if(d_MIds == NULL)
	{
		d_MCount = mIds.size();
		cudaMalloc((void**) &d_MIds, sizeof(int)*d_MCount);
		cudaMemcpy(d_MIds, mIds.data(), sizeof(int)*d_MCount, cudaMemcpyHostToDevice);

		cudaMalloc((void**) &d_BLengths, sizeof(float)*d_MCount);
		cudaMemcpy(d_BLengths, blengths.data(), sizeof(float)*d_MCount, cudaMemcpyHostToDevice);
	}
	dim3  grid( 5*10, 5*10, 1);
	dim3  threads( 5, 5, 1);
	springbreakKernel<<< grid, threads>>>(d_Pos, d_Frc, d_Vel, d_MIds, d_BLengths, d_MCount/2);

	cudaError_t err = cudaGetLastError();
	if(err != cudaSuccess)
		std::cerr << err << " " << cudaGetErrorString(err) << std::endl;
}

void cudaAutoCollide()
{
	if(d_Pos == NULL)
		return;

	dim3  grid( 5*25, 5*25, 1);
	dim3  threads( 5, 5, 1);
	autoCollideKernel<<< grid, threads>>>(d_Pos, d_Frc, d_Vel, d_MCount);
}


bool cudaSnapshot(std::vector<glm::vec3>& pos)
{
	if(d_Pos)
	{
		cudaMemcpy(pos.data(), d_Pos, sizeof(glm::vec3)*d_MSize, cudaMemcpyDeviceToHost);
		return true;
	}
	return false;
}