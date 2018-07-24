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
	Counter cnt;
	Pos listenerPos;
	SoundEngine::SoundSource appSound;
	SoundEngine::SoundSource exproSound;
	Texture tex;
	Model model;
	std::vector<std::unique_ptr<EnemyData>> data;
	std::unique_ptr<EnemyData> AddEnemy();
	//体力を監視する
	void LifeCheck();
	//新しい敵を生成する
	void Create();
	//アクティブでないものを処刑する
	void Executioners();
	static constexpr float RADIUS = 2.5f;
	int efHandle;
	bool isAbduction = false;
public:
	void SetListenerPos(Pos&& pos);
	ThiefComponent();
	void Damaged(Entity& e);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	void SetTrackingTarget(Entity& target);
	const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::GetData() const;
	
};