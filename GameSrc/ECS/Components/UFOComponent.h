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
	//体力を監視する
	void LifeCheck();
	//新しい敵を生成する
	void Create(const float& theta);
	//アクティブでないものを処刑する
	void Refresh();
	//出現角度を決めてその値を返す
	const float GetTheta() const;
	static constexpr float FieldOut = 500;
	static constexpr float RADIUS = 2.5f;
	static constexpr float UpMoveMAX = 20;
	static constexpr float HeightMax = 10;
	int efHandle;
	bool isNotFound;
public:
	//効果音のリスナーをセット
	void SetListenerPos(Pos&& pos);
	UFOComponent();
	//当たり判定を行いたいEntityをセット
	void Damaged(Entity& e);
	//索敵範囲に入ったか
	bool IsToBeInRange(Sphere& sphere, long long& id_);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	//追跡したいターゲットをセット
	void SetTrackingTarget(Entity& target) noexcept;
	//データ取得
	[[nodiscard]] const std::vector<std::unique_ptr<EnemyData>>& UFOComponent::GetData() const;
	//残り時間をセットする
	void SetTimeLimit(const Counter& limit);

	
};