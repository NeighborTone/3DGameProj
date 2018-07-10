#include "MeshComponent.h"

void MeshComponent::LoadTexture(const char * Texturepath)
{
	tex.Load(Texturepath);
}

void MeshComponent::LoadShader(const char * shaderPath)
{
	mesh.GetMaterial().Load(shaderPath);
}

MeshComponent::MeshComponent(const char* Texturepath)
{
	tex.Load(Texturepath);
}
MeshComponent::MeshComponent(const char* Texturepath, const char* shaderPath)
{
	tex.Load(Texturepath);
	mesh.GetMaterial().Load(shaderPath);
}
void MeshComponent::SetMaterial(const char * Texturepath, const char * shaderPath)
{
	LoadTexture(Texturepath);
	LoadShader(shaderPath);
}
void MeshComponent::SetTransform(Pos && pos, Velocity && velocity, Angles && angle, Scale && scale)
{
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>(Pos(pos), Velocity(velocity), Angles(angle), Scale(scale));
	}
}
bool MeshComponent::CreateCube(bool shouldClear)
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
bool MeshComponent::CreateSphere(float radius, int tessellation, bool shouldClear)
{
	if (!isCreate)
	{
		mesh.CreateSphere(radius * 2, tessellation, shouldClear);
		mesh.GetMaterial().SetTexture(0, &tex);
		isCreate = true;
		return isCreate;
	}
	return isCreate;
}
void MeshComponent::Initialize()
{
	isCreate = false;
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>();
		transform = &entity->GetComponent<TransformComponent>();
		mesh.pos = transform->pos;
		mesh.angle = transform->angle;
		mesh.scale = transform->scale;
	}
	else
	{
		mesh.pos = 0;
		mesh.angle = 0;
		mesh.scale = 1;
	}

}
void MeshComponent::UpDate()
{
	mesh.pos = transform->pos;
	mesh.angle = transform->angle;
}
void MeshComponent::Draw3D()
{
	mesh.Draw();
}
