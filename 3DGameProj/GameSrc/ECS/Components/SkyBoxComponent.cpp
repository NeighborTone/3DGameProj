#include "SkyBoxComponent.h"

SkyBoxComponent::SkyBoxComponent(std::string texturePath)
{
	tex.Load(texturePath);
}

void SkyBoxComponent::SetPos(Pos&& pos)
{
	trans->pos = pos;
}

void SkyBoxComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>();
	}
	trans = &entity->GetComponent<TransformComponent>();
	sky.GetMaterial().Load("Resource/Shader/Sky.hlsl");
	sky.GetMaterial().SetTexture(0, &tex);
	sky.CreateSphere(1,24);
	sky.scale = 1000;
}

void SkyBoxComponent::UpDate()
{
	sky.pos = trans->pos;
	sky.angle = trans->angle;
}

void SkyBoxComponent::Draw3D()
{
	sky.Draw();
}

