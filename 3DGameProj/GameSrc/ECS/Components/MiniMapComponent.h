#pragma once
#include "../ECS.hpp"
#include "../Components/Transform.hpp"
#include "../../Engine.h"
#include <vector>
#include <memory>
class MiniMapComponent : public Component
{
private:
	static constexpr float mapRadius = 128;
	Sprite map;
	Sprite topping;
	Sprite enemyIcon;
public:

	MiniMapComponent();
	const void DrawEnemys(const Entity& enemy, Entity& player);
	const void DrawTopping(const Entity& topping_, Entity& player);
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;

};