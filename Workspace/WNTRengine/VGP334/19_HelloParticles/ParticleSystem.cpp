
#include "ParticleSystem.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Physics;
using namespace WNTRengine::WNTRmath;


void ParticleSystem::Initialize(const ParticleSystemInfo& info)
{
	mInfo = info;
	mNextAvailableParticleIndex = 0;
	mNextSpawn = 0.0f;
	mLifeTime = 0.0f;
	mParticles.resize(info.maxParticles);
	for (auto& p : mParticles)
	{
		p.Initialize();
	}
}
void ParticleSystem::Terminate()
{
	for (auto& p : mParticles)
	{
		p.Terminate();
	}
}
void ParticleSystem::Update(float deltaTime)
{
	if (mLifeTime > 0.0f)
	{
		mNextSpawn -= deltaTime;
		mLifeTime -= deltaTime;
		if (mNextSpawn <= 0.0f)
		{
			SpawnParticles();
		}
		for (auto& p : mParticles)
		{
			p.Update(deltaTime);
		}
	}
}

void ParticleSystem::DebugUI()
{

}


void ParticleSystem::SpawnParticles()
{
	int numParticles = mInfo.minParticlePermit + (rand() % (mInfo.maxParticlePermit - mInfo.minParticlePermit));
	for (int i = 0; i < numParticles; ++i)
	{
		SpawnParticle();
	}
	mNextSpawn = mInfo.spawnDelay;

}														   
void ParticleSystem::SpawnParticle()
{
	Particle& p = mParticles[mNextAvailableParticleIndex];
	mNextAvailableParticleIndex = (mNextAvailableParticleIndex + 1) % mParticles.size();
}