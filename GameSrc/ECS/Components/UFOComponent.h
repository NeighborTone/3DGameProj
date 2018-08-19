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

class UFOComponent : public Component
{
private:
	float addedSpeed;
	static long long id_;
	Counter cnt;
	const Counter* pTimelimit;
	Pos listenerPos;
	SoundEngine::SoundSource appSound;
	SoundEngine::SoundSource exproSound;
	std::vector<std::unique_ptr<EnemyData>> data;
	std::unique_ptr<EnemyData> AddEnemy();
	//�̗͂��Ď�����
	void LifeCheck();
	//�V�����G�𐶐�����
	void Create(const float& theta);
	//�A�N�e�B�u�łȂ����̂����Y����
	void Refresh();
	//�o���p�x�����߂Ă��̒l��Ԃ�
	const float GetTheta() const;
	static constexpr float FieldOut = 500;
	static constexpr float RADIUS = 2.5f;
	static constexpr float UpMoveMAX = 20;
	static constexpr float HeightMax = 10;
	int efHandle;
	bool isNotFound;
public:
	//���ʉ��̃��X�i�[���Z�b�g
	void SetListenerPos(Pos&& pos);
	UFOComponent();
	//�����蔻����s������Entity���Z�b�g
	void Damaged(Entity& e);
	//���G�͈͂ɓ�������
	bool IsToBeInRange(Sphere& sphere, long long& id_);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	//�ǐՂ������^�[�Q�b�g���Z�b�g
	void SetTrackingTarget(Entity& target) noexcept;
	//�f�[�^�擾
	[[nodiscard]] const std::vector<std::unique_ptr<EnemyData>>& UFOComponent::GetData() const;
	//�c�莞�Ԃ��Z�b�g����
	void SetTimeLimit(const Counter& limit);

	
};