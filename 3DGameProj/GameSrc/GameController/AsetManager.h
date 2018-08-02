#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include "../../Graphics/Model.h"
#include "../ECS/Components/ComponentData/MetaData.hpp"
#include <unordered_map>

//���I�ɃI�u�W�F�N�g�𐶐��������̂�
//���[�h���d�����̂�풓�����������\�[�X�͋N�����Ɋm�ۂ���
class Models
{
private:
	std::unordered_map<std::string, std::pair<std::unique_ptr<Model>, std::unique_ptr<Texture>>> models;
public:
	void AddModel(std::string name, std::string modelPath, std::string textPath);
	void DrawModel(std::string name, TransForm& trans);
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