#include "MeshComponent.h"

MeshComponent::MeshComponent(const char* Texturepath)
{
	tex.Load(Texturepath);
}
MeshComponent::MeshComponent(const char* Texturepath, const char* shaderPath)
{
	tex.Load(Texturepath);
	mesh.GetMaterial().Load(shaderPath);
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
	transform = &entity->GetComponent<TransformComponent>();
	mesh.pos = transform->pos;
	mesh.angle = transform->angle;
	mesh.scale = transform->scale;
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
