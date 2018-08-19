#include "SkyBoxComponent.h"
#include "../../GameController/GameController.h"
SkyBoxComponent::SkyBoxComponent(std::string texturePath)
{
	tex.Load(texturePath);
	skyHandle = AsetManager::GetParticle().Play("sky", Vec3(0, 0, 0));
}

void SkyBoxComponent::SetPos(Pos&& pos)
{
	trans->pos = pos;
	AsetManager::GetParticle().SetPos(skyHandle,Pos(trans->pos));
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
	sky.scale = 10000;
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

