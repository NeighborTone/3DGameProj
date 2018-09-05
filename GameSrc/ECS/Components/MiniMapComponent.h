#pragma once
#include "../ECS.hpp"
#include "../Components/Transform.hpp"
#include "../../Engine.h"
#include <vector>
#include <memory>
class MiniMapComponent : public Component
{
private:
	static constexpr float MapRadius = 128;
	static constexpr float ExpansionRate = 1.2f;
	Sprite map;
	Sprite targetIcon;
	Sprite enemyIcon;
public:

	MiniMapComponent();
	const void DrawEntityes(const Entity& entity, Entity& player);
	void Initialize() STUB

	void UpDate() STUB

	void Draw3D() STUB

	void Draw2D() override;

};