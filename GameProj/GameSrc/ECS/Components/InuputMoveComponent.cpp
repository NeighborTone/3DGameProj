#include "InuputMoveComponent.h"

InuputMoveComponent::InuputMoveComponent(const float speed)
{
	speed_ = speed;
}
void InuputMoveComponent::Initialize()
{
	transform = &entity->GetComponent<TransformComponent>();
}
void InuputMoveComponent::UpDate()
{
	if (KeyBoard::On(KeyBoard::Key::KEY_UP))
	{
		transform->pos.z += transform->velocity.z;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
	{
		transform->pos.z -= transform->velocity.z;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_LEFT))
	{
		transform->pos.x -= transform->velocity.x;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_RIGHT))
	{
		transform->pos.x += transform->velocity.x;
	}
	transform->angle.x += Mouse::GetMousePosCenter().y * speed_;
	transform->angle.y += Mouse::GetMousePosCenter().x * speed_;

	Mouse::SetMousePos(0, 0);
}

void InuputMoveComponent::Draw2D() 
{
	Mouse::DrawCursor(false);
}