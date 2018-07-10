#include "SkyBoxComponent.h"

SkyBoxComponent::SkyBoxComponent(std::string texturePath)
{
	tex.Load(texturePath);
}

void SkyBoxComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>();
	}
	sky.GetMaterial().Load("Resource/Shader/Sky.hlsl");
	sky.GetMaterial().SetTexture(0, &tex);
	sky.CreateSphere(1,24);
	sky.scale = 1000;
}

void SkyBoxComponent::UpDate()
{
	sky.angle.y -= 0.5f;
}

void SkyBoxComponent::Draw3D()
{
	sky.Draw();
}

