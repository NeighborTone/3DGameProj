#include "ShotComponent.h"

ShotComponent::ShotComponent()
{
	tex.Load("Resource/texture/stonewall_diff.jpg");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere();
}

void ShotComponent::Initialize()
{
	trans = &entity->GetComponent<TransformComponent>();
	shotMove = &entity->GetComponent<InputShotComponent>();
	mesh.pos = trans->pos;
}

void ShotComponent::UpDate()
{
	mesh.pos = trans->pos;
	mesh.angle = trans->angle;
}

void ShotComponent::Draw3D()
{
	
	mesh.Draw();

}

