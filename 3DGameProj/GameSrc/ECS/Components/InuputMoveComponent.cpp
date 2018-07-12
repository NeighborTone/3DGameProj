#include "InuputMoveComponent.h"

void InuputMoveComponent::MoveForwardAndBack()
{
	if (KeyBoard::On(KeyBoard::Key::KEY_W))
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_S))
	{
		transform->pos -= dir;
	}
}

void InuputMoveComponent::MoveLeftAndRight()
{
	if (KeyBoard::On(KeyBoard::Key::KEY_D))
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_A))
	{
		transform->pos -= dir;
	}
}

void InuputMoveComponent::FixedMovableAngle()
{
	if (transform->angle.x >= 40)
	{
		transform->angle.x = 40;
	}
	if (transform->angle.x <= -90)
	{
		transform->angle.x = -90;
	}
}

void InuputMoveComponent::ManipulationOfView()
{
	transform->angle.x += Mouse::GetMousePosCenter().y * speed_;
	transform->angle.y += Mouse::GetMousePosCenter().x * speed_;
}

void InuputMoveComponent::ForwardAndBackwardDirection()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y + 90)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y + 90)) * transform->velocity.z;
}

void InuputMoveComponent::LeftAndRightDirection()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y)) * transform->velocity.z;
}

InuputMoveComponent::InuputMoveComponent(const float speed)
{
	speed_ = speed;
}
void InuputMoveComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		transform = &entity->AddComponent<TransformComponent>();
	}
	transform = &entity->GetComponent<TransformComponent>();
	eyeHeight = transform->pos.y;
}
void InuputMoveComponent::UpDate()
{
	ForwardAndBackwardDirection();
	MoveForwardAndBack();
	LeftAndRightDirection();
	MoveLeftAndRight();
	transform->pos.y = eyeHeight;
	ManipulationOfView();
	FixedMovableAngle();

	Mouse::SetMousePos(0, 0);
}
