#include "InuputMoveComponent.h"
#include "ComponentData/Collision.h"
void InuputMoveComponent::MoveForwardAndBack()
{
	const bool isOut = abs(transform->pos.GetDistance(Pos(0, 0, 0))) >= 500;
	if (!isOut)
	{
		prePos = transform->pos;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_W) && !isOut)
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_S) && !isOut)
	{
		transform->pos -= dir;
	}
	if(isOut)
	{
		transform->pos = prePos;
	}
}

void InuputMoveComponent::MoveLeftAndRight()
{
	const bool isOut = abs(transform->pos.GetDistance(Pos(0, 0, 0))) >= 500;
	if (!isOut)
	{
		prePos = transform->pos;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_D) && !isOut)
	{
		transform->pos += dir;
	}
	if (KeyBoard::On(KeyBoard::Key::KEY_A) && !isOut)
	{
		transform->pos -= dir;
	}
	if (isOut)
	{
		transform->pos = prePos;
	}
}

void InuputMoveComponent::FixedMovableAngle()
{
	if (transform->angle.x >= DownMax)
	{
		transform->angle.x = DownMax;
	}
	if (transform->angle.x <= UpMax)
	{
		transform->angle.x = UpMax;
	}
}

void InuputMoveComponent::ManipulationOfView()
{
	transform->angle.x += Mouse::GetMousePosCenter().y * speed_;
	transform->angle.y += Mouse::GetMousePosCenter().x * speed_;
}

void InuputMoveComponent::ForwardAndBackwardDirection()
{
	dir.x = cosf(DirectX::XMConvertToRadians(-transform->angle.y + DirOffSet)) * cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-transform->angle.x)) * transform->velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-transform->angle.x)) * sinf(DirectX::XMConvertToRadians(-transform->angle.y + DirOffSet)) * transform->velocity.z;
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

	//‰ŠúˆÊ’u‚ð•Û‘¶‚µ‚Ä‚¨‚­
	static bool isInit = false;
	if (!isInit)
	{
		isInit = true;
		initPos = transform->pos;
	}
	//ŽŸ‰ñˆÈ~‚Ì‰Šú‰»‚É‚Í•Û‘¶‚µ‚½’l‚ð—p‚¢‚é
	transform->pos = initPos;
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

void InuputMoveComponent::Draw2D()
{
	t.Create("prex" + std::to_string(prePos.x) + "::" + "prez" + std::to_string(prePos.z));
	t.color = Float4(1, 1, 1, 1);
	t.pos.y = 20;
	t.pos.x = -500;
	t.Draw();
	t.Create("distance" + (std::to_string(abs(transform->pos.GetDistance(Pos(0, 0, 0))))));
	t.color = Float4(1, 1, 1, 1);
	t.pos.y = 40;
	t.pos.x = -500;
	t.Draw();
	t.Create("x"+ std::to_string(transform->pos.x) + "::" + "z" + std::to_string(transform->pos.z));
	t.color = Float4(1, 1, 1, 1);
	t.pos.y = 0;
	t.pos.x = -500;
	t.Draw();
}
