#pragma once
#include "../ECS.hpp"
#include "../Components/Transform.hpp"
#include "../../Engine.h"
#include <vector>
#include <memory>
class MiniMapComponent : public Component
{
private:
	TransformComponent* trans;
	Sprite map;
	Sprite enemys;
public:

	MiniMapComponent();

	void Initialize() override;

	void UpDate() override;

	void Draw3D() STUB

	void Draw2D() override;

};