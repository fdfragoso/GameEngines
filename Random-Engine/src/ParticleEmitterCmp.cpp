
#include "ParticleEmitterCmp.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <glm/gtc/random.hpp>

#include "RandomEngine.hpp"

using namespace SRE;

ParticleEmitterCmp::ParticleEmitterCmp(GameObject *gameObject)
	: Component(gameObject)
{
}

Particle::Particle(glm::vec3 position, glm::vec3 velocity, float timeOfBirth, glm::vec4 color, float size)
	: position(position), velocity(velocity), timeOfBirth(timeOfBirth), color(color), size(size)
{
}

ParticleEmitterCmp::~ParticleEmitterCmp(){
	particles.clear();
	delete mesh;
	delete myTex;
}

void ParticleEmitterCmp::setUp(int size, SRE::Texture * myTex) {
	this->particleMat = RandomEngine::particleMat;
	this->myTex = myTex;
	mesh = nullptr;
	currentTime = 0.0f;
	emissionIndex = 0;
	for (int i = 0; i<size; i++) {
		particles.push_back(Particle(glm::vec3{ 0,0,0 }, getVelocity(), -999999, getColor(), glm::linearRand(1.0f, 5.0f)));
		finalPos.push_back(glm::vec3{ 0,0,0 });
		float s0 = particles[i].size;
		sizes.push_back(s0);
		glm::vec4 c0 = particles[i].color;
		colors.push_back(c0);
		glm::vec2 uv0 = glm::vec2(0, 0);
		uvs.push_back(uv0);
		float us0 = 1.0f;
		uvSize.push_back(us0);
		float ur0 = 0.0f;
		uvRotation.push_back(ur0);
	}
	mesh = new SRE::ParticleMesh(finalPos, colors, uvs, uvSize, uvRotation, sizes);
}

void ParticleEmitterCmp::emit(glm::vec3 position, glm::vec3 velocity) {
	particles[emissionIndex].timeOfBirth = currentTime;
	particles[emissionIndex].position = position;
	particles[emissionIndex].velocity = velocity;
	emissionIndex = (emissionIndex + 1) % particles.size();
}

void ParticleEmitterCmp::update() {
	glm::vec3 a(0, gravity, 0);
	for (int i = 0; i<particles.size(); i++) {
		float t = currentTime - particles[i].timeOfBirth;
		auto v0 = particles[i].velocity;
		auto p0 = particles[i].position;
		float s0 = particles[i].size;
		finalPos[i] = 0.5f*a*t*t + v0*t + p0;
		//color change
		//glm::vec4 colorChange = glm::linearRand(glm::vec4(-0.1f, -0.1f, -0.1f, -0.02f), glm::vec4(0.1f, 0.1f, 0.1f, +0.02f));
		//glm::clamp(colors[i] += colorChange, { 0, 0, 0, 0 }, { 1, 1, 1, 1 });
		colors[i] = getColor();
		//size change
		float sizeChange = glm::linearRand(-0.02f, 0.02f);
		glm::clamp(sizes[i] += sizeChange, 0.0f, 1.0f);
	}
	mesh->update(finalPos, colors, uvs, uvSize, uvRotation, sizes);
	currentTime += RandomEngine::deltaTimeSec;
}

void ParticleEmitterCmp::render() {
	if (myTex != nullptr) {
		particleMat->buildMat(myTex);
	} else {
		particleMat->buildMat();
	}
	SimpleRenderEngine::instance->draw(mesh, glm::mat4(1), particleMat->shader);
}

glm::vec4 ParticleEmitterCmp::getColor() {
	if (isSolidColor) {
		return minColor;
	} else {
		//Interpolation time by default 1 sec
		float t = currentTime - (long)currentTime;
		return RandomInterpolation::interpolate(minColor, maxColor, t, interpolationType);
	}
}

void ParticleEmitterCmp::setColor(glm::vec4 color) {
	isSolidColor = true;
	this->minColor = color;
}

void ParticleEmitterCmp::setColor(glm::vec4 minColor, glm::vec4 maxColor, InterpolationType i) {
	isSolidColor = false;
	this->minColor = minColor;
	this->maxColor = maxColor;
	this->interpolationType = i;
}

void ParticleEmitterCmp::setVelocity(glm::vec3 velocity) {
	this->staticVelocity = velocity;
}

glm::vec3 ParticleEmitterCmp::getVelocity() {
		return staticVelocity;
	}
