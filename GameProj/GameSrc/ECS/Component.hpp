#pragma once
#include "ECS.hpp"
#include <Windows.h>
#include <iostream>
#include <string>
#include "../../Engine.h"
#include "../../Engine/Graphics/Particle.h"

#define STUB override {}
using Pos = Vec3;
using Velocity = Vec3;
using Angles = Vec3;
using Scale = Vec3;
class TransformComponent : public Component
{
public:
	Pos pos;
	Velocity velocity;
	Angles angle;
	Scale scale;
	TransformComponent() = default;
	TransformComponent(Pos&& pos, Velocity&& velocity, Angles&& angle, Scale&& scale):
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
	float speed_;
	TransformComponent* transform;
public:
	InuputComponent(const float speed)
	{
		speed_ = speed;
	}
	void Initialize() override
	{
		transform = &entity->GetComponent<TransformComponent>();
	}
	void UpDate() override
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
		camera3D.pos = transform->pos;

		camera3D.SetPerspective(45.0f, 1, 10000.0f);
		camera3D.SetDepthTest(true);

		camera2D.SetDepthTest(false);
		camera2D.SetOrthographic(1, 0.1f, 1000.0f);
	}

	void UpDate() override
	{
		camera3D.pos = transform->pos;
		camera3D.angle = transform->angle;
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

class MeshComponent : public Component
{
private:
	bool isCreate;
	TransformComponent* transform;
	Texture tex;
	Mesh mesh;
public:
	MeshComponent(const char* Texturepath)
	{
		tex.Load(Texturepath);
	}
	MeshComponent(const char* Texturepath, const char* shaderPath)
	{
		tex.Load(Texturepath);
		mesh.GetMaterial().Load(shaderPath);
	}
	bool CreateCube(bool shouldClear = true)
	{
		if (!isCreate)
		{
			mesh.CreateCube(shouldClear);
			mesh.GetMaterial().SetTexture(0, &tex);
			isCreate = true;
			return isCreate;
		}
		return isCreate;
	}
	bool CreateSphere(float radius = 0.5f, int tessellation = 10, bool shouldClear = true)
	{
		if (!isCreate)
		{
			mesh.CreateSphere(radius * 2,tessellation,shouldClear);
			mesh.GetMaterial().SetTexture(0, &tex);
			isCreate = true;
			return isCreate;
		}
		return isCreate;
	}
	void Initialize() override
	{
		isCreate = false;
		transform = &entity->GetComponent<TransformComponent>();
		mesh.pos = transform->pos;
		mesh.angle = transform->angle;
		mesh.scale = transform->scale;
	}
	void UpDate() override
	{
		mesh.pos = transform->pos;
		mesh.angle = transform->angle;
	}
	void Draw3D() override
	{
		mesh.Draw();
	}
	void Draw2D() STUB
};
