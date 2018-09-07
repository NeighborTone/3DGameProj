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
	std::vector<TomatoData> data;
	void Refresh();
public:
	TomatoComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	//ゲームが終了したらクリアする
	void EndRefresh(const GameState& state);
	//データ取得
	[[nodiscard]] const std::vector<TomatoData>& GetData() const;
	//攫われているときの動作
	void ToBeKidnapped(Entity& enemy);
};
