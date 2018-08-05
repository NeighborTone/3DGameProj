#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"
#include "../Components/ComponentData/MetaData.hpp"
#include <vector>

//UFOにさらわれないように守るトマト
//全部さらわれるとゲームオーバーになります
class TomatoComponent : public Component
{
private:
	static constexpr float FieldOut = 490;
	static constexpr float OnGround = 4;
	Mesh mesh;
	Texture tex;
	std::vector<ToppingData> data;
	void Executioners();
public:
	TomatoComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB

	void GameOver(GameState& state) const;
	//データ取得
	[[nodiscard]] const std::vector<ToppingData>& GetData() const;
	//攫われているときの動作
	void ToBeKidnapped(Entity& enemy);
};
