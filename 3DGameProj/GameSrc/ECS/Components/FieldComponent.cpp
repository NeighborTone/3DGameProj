#include "FieldComponent.h"

FieldComponent::FieldComponent()
{
	tex.Load("Resource/Texture/w.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(1,26);
}

void FieldComponent::Initialize()
{
	mesh.scale = 1000;
	mesh.scale.y = 1;

}

void FieldComponent::UpDate()
{
}

void FieldComponent::Draw3D()
{
	mesh.Draw();
}

void FieldComponent::Draw2D()
{
}
