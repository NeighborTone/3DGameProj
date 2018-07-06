#pragma once
#include "ECS.hpp"
#include <Windows.h>
#include <iostream>
#include "../../Engine.h"
#include "../../Engine/Graphics/Particle.h"

#define STUB override {}

class TransformComponent : public Component
{

public:
	Vec3 pos;
	Vec3 velocity;
	Vec3 angle;
	Vec3 scale;
	TransformComponent() = default;
	TransformComponent(Vec3&& pos,Vec3&& velocity,Vec3&& angle,Vec3&& scale):
		pos(pos),
		velocity(velocity),
		angle(angle),
		scale(scale)
	{}
	void Initialize() STUB

	void UpDate() STUB

	void Draw3D() STUB

	void Draw2D() STUB

};

class InuputComponent : public Component
{
private:
	TransformComponent* transform;
public:

	void Initialize() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}
	void UpDate() override
	{
		if (KeyBoard::On(KeyBoard::Key::KEY_UP))
		{
			transform->pos.z += 0.6f;
		}
		if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
		{
			transform->pos.z -= 0.6f;
		}
		if (KeyBoard::On(KeyBoard::Key::KEY_LEFT))
		{
			transform->pos.x -= 0.6f;
		}
		if (KeyBoard::On(KeyBoard::Key::KEY_RIGHT))
		{
			transform->pos.x += 0.6f;
		}
		transform->angle.x += Mouse::GetMousePosCenter().y * 0.3f;
		transform->angle.y += Mouse::GetMousePosCenter().x * 0.3f;

		Mouse::SetMousePos(0, 0);
	}
	void Draw3D() STUB
	
	void Draw2D() override
	{
		Mouse::DrawCursor(false);
	}
};

//仮処理、後でファイルを分ける
class CameraComponent : public Component
{
private:
	TransformComponent* transform;
	Camera camera3D;
	Camera camera2D;
public:
	void Initialize() override
	{
		transform = &entity->GetComponent<TransformComponent>();
		camera3D.pos.z = transform->pos.z;
		camera3D.pos.y = transform->pos.y;

		camera3D.SetPerspective(45.0f, 1, 10000.0f);
		camera3D.SetDepthTest(true);

		camera2D.SetDepthTest(false);
		camera2D.SetOrthographic(1, 0.1f, 1000.0f);
	}

	void UpDate() override
	{
		camera3D.pos.z = transform->pos.z;
		camera3D.pos.x = transform->pos.x;
		camera3D.angle.x = transform->angle.x;
		camera3D.angle.y = transform->angle.y;
	}

	void Project3D()
	{
		camera3D.Run(true);
	}

	void Project2D()
	{
		camera2D.Run(false);
	}
	void Draw3D() STUB

	void Draw2D() STUB

	const Camera& GetCamera3D() const
	{
		return camera3D;
	}

};
