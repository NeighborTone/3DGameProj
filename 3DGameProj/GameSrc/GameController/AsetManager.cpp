#include "AsetManager.h"

void AsetManager::LoadModels()
{
	GetModels().AddModel(
		"UFO", 
		"Resource/Model/ufo.fbx",
		"Resource/Texture/UFO_D.png");
}

void AsetManager::LoadParticle()
{
	GetParticle().AddEffect("sky", "Resource/Effect/stars.efk");
	GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	GetParticle().AddEffect("sucking", "Resource/Effect/suck.efk");
	GetParticle().AddEffect("away", "Resource/Effect/away.efk");
}


void Models::AddModel(std::string name, std::string modelPath, std::string textPath)
{
	models[name] = std::make_pair(
		std::make_unique<Model>(modelPath), 
		std::make_unique<Texture>(textPath));
}

void Models::DrawModel(std::string name, TransForm& trans)
{
	models[name].first->pos = trans.pos;
	models[name].first->scale = trans.scale;
	models[name].first->angle = trans.angles;
	models[name].second->Attach(0);
	models[name].first->Draw();
}

Particle& AsetManager::GetParticle()
{
	static std::unique_ptr<Particle> ef = std::make_unique<Particle>();
	return *ef;
}

Models& AsetManager::GetModels()
{
	static std::unique_ptr<Models> models = std::make_unique<Models>();
	return *models;
}

void AsetManager::LoadAset()
{
	static bool isInit = false;
	if (!isInit)
	{
		LoadModels();
		LoadParticle();
	}
	
}
