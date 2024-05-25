#pragma once

#include <vector>
#include <thread>

#include "GL/glew.h"
#include <glm/glm.hpp>

#include "Particle.h"
#include "Geometry.h"

/// Settings which can alter the SPH simulation
struct SPHSettings
{
	// 0.02f, 1000, 1, 1.04f, 0.15f, -9.8f, 0.2f
    SPHSettings(
        float mass, float restDensity, float gasConst, float viscosity,
        float h, float g, float tension);

    glm::mat4 sphereScale;
    float poly6, spikyGrad, spikyLap, gasConstant, mass, h2, selfDens,
        restDensity, viscosity, h, g, tension, massPoly6Product;
};

class SPHSystem
{
private:
    SPHSettings settings;
    size_t particleCubeWidth;

	bool started;
    bool runOnGPU;

	//initializes the particles that will be used
	void initParticles();

	// Sphere geometry for rendering
	Geometry* sphere;
	glm::mat4* sphereModelMtxs;
	GLuint vbo;

public:
	SPHSystem(
        size_t numParticles, const SPHSettings &settings,
        const bool &runOnGPU);
	~SPHSystem();

	Particle *particles;
    size_t particleCount;

	//updates the SPH system
	void update(float deltaTime);

	//draws the SPH system & its particles
	void draw(const glm::mat4& viewProjMtx, GLuint shader);

	void reset();
	void startSimulation();
};

