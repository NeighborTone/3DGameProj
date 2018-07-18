#pragma once
#include "../../../Engine/Utilitys/Randam.hpp"
#include "../../GameController/GameController.h"
#include "../Components/ComponentData/MetaData.hpp"
#include "../ECS.hpp"
#include "../Components/ComponentData/AABB.hpp"
#include <vector>
#include <memory>
class ThiefComponent : public Component
{
private:
	Pos  listenerPos;
	SoundEngine::SoundSource appSound;
	SoundEngine::SoundSource exproSound;
	Texture tex;
	Mesh mesh;
	std::vector<std::unique_ptr<MetaData>> data;
	std::unique_ptr<MetaData> AddEnemy();
	//�̗͂��Ď�����
	void LifeCheck();
	//�V�����G�𐶐�����
	void Create();
	//�A�N�e�B�u�łȂ����̂����Y����
	void Executioners();
	float radius;
public:
	void SetListenerPos(Pos&& pos);
	ThiefComponent(const float r);
	void Damaged(Entity& e);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
};