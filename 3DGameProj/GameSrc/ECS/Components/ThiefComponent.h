#pragma once
#include "../../../Engine/Utilitys/Randam.hpp"
#include "../../GameController/GameController.h"
#include "../Components/ComponentData/MetaData.hpp"
#include "../ECS.hpp"
#include "../../../Engine/Utilitys/Counter.hpp"
#include "../Components/ComponentData/AABB.hpp"
#include "../../../Engine/Graphics/Model.h"
#include <vector>
#include <memory>
class ThiefComponent : public Component
{
private:
	//$Test$
	static long long id_;
	Counter cnt;
	Pos listenerPos;
	SoundEngine::SoundSource appSound;
	SoundEngine::SoundSource exproSound;
	Texture tex;
	Model model;
	std::vector<std::unique_ptr<EnemyData>> data;
	std::unique_ptr<EnemyData> AddEnemy();
	//�̗͂��Ď�����
	void LifeCheck();
	//�V�����G�𐶐�����
	void Create();
	//�A�N�e�B�u�łȂ����̂����Y����
	void Executioners();
	static constexpr float RADIUS = 2.5f;
	static constexpr float UpMoveMAX = 20;
	static constexpr float HeightMax = 10;
	int efHandle;
	bool isNotFound;
public:
	//���ʉ��̃��X�i�[���Z�b�g
	void SetListenerPos(Pos&& pos);
	ThiefComponent();
	//�����蔻����s������Entity���Z�b�g
	void Damaged(Entity& e);
	//���G�͈͂ɓ�������
	bool IsToBeInRange(Sphere& sphere, long long& id_);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	//�ǐՂ������^�[�Q�b�g���Z�b�g
	void SetTrackingTarget(Entity& target);
	const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::GetData() const;
	
};