#pragma once
#include "../../../Engine/Utilitys/Randam.hpp"
#include "../../GameController/GameController.h"
#include "../Components/ComponentData/EnemyData.hpp"
#include "../ECS.hpp"
#include "../Components/ComponentData/AABB.hpp"
#include <vector>
#include <memory>
class ThiefComponent : public Component
{
private:
	Pos*  pos_;
	SoundEngine::SoundSource sound;
	Texture tex;
	std::vector<std::unique_ptr<EnemyData>> data;
	std::unique_ptr<EnemyData> AddEnemy();
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
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	//�G�̏��𓾂�
	const std::vector<std::unique_ptr<EnemyData>>& Get() const;
};