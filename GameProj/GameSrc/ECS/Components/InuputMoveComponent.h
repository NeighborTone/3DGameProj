#pragma once
#include "Transform.hpp"

class InuputMoveComponent : public Component
{
private:
	float speed_;
	TransformComponent* transform;
public:
	InuputMoveComponent(const float speed);
	void Initialize() override;

	void UpDate() override;
	
	void Draw3D() STUB

	void Draw2D() override;

};