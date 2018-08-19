#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include "../../Graphics/Model.h"
#include "../ECS/Components/ComponentData/MetaData.hpp"
#include <unordered_map>

//動的にオブジェクトを生成したいので
//ロードが重いものや常駐させたいリソースは起動時に確保する
class Models
{
private:
	std::unordered_map<std::string, std::pair<std::unique_ptr<Model>, std::unique_ptr<Texture>>> models;
public:
	void AddModel(const std::string& name, const std::string& modelPath, const std::string& textPath);
	void DrawModel(const std::string& name, const TransForm& trans);
};

class AsetManager
{
private:
	static void LoadModels();
	static void LoadParticle();

public:
	AsetManager() = delete;
	~AsetManager() = default;
	static Particle& GetParticle();
	static Models& GetModels();
	static void LoadAset();
};