#pragma once
#include "../ECS.hpp"
#include "../Components/Transform.hpp"
#include "../../Engine.h"
#include <vector>
#include <memory>
class MiniMapComponent : public Component
{
private:
	Sprite map;
	Sprite topping;
	Sprite enemyIcon;
public:

	MiniMapComponent();
	void DrawEnemys(Entity& enemy,Entity& player);
	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;

};