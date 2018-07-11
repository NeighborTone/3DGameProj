#include "InuputMoveComponent.h"

InuputMoveComponent::InuputMoveComponent(const float speed)
{
	speed_ = speed;
}
void InuputMoveComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		return;
	}
	transform = &entity->GetComponent<TransformComponent>();
}
void InuputMoveComponent::UpDate()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y + 90)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y + 90)) * transform->velocity.z;
	if (KeyBoard::On(KeyBoard::Key::KEY_UP))
	{	
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
	{
		transform->pos -= dir;
	}
	/*if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
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
	}*/
	transform->angle.x += Mouse::GetMousePosCenter().y * speed_;
	transform->angle.y += Mouse::GetMousePosCenter().x * speed_;

	Mouse::SetMousePos(0, 0);
}
