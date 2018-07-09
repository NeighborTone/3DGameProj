#include"InputShotComponent.h"

InputShotComponent::InputShotComponent(const float speed) :
	speed_(speed),
	isActive(false),
	deathTime(0)
{}

void InputShotComponent::Initialize()
{
	deathTime = 0;
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>();
	}
	transform = &entity->GetComponent<TransformComponent>();
}

void InputShotComponent::UpDate()
{
	if (isActive)
	{
		transform->pos += transform->velocity;
		++deathTime;
	}

	if (deathTime > 80 && isActive)
	{
		deathTime = 0;
		isActive = false;
	}
}

bool InputShotComponent::IsActive()
{
	return isActive;
}

void InputShotComponent::Shot(TransformComponent&& trans)
{
	if (isActive)
	{
		return;
	}
	bool isShot = Mouse::L_On() % 8 == 1;
	if (isShot && !isActive)
	{
		transform->pos = trans.pos;

		transform->velocity.x = cosf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
		transform->velocity.y = sinf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
		transform->velocity.z = cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * sinf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * speed_;
		transform->pos += transform->velocity;
		isActive = true;
	}
}

