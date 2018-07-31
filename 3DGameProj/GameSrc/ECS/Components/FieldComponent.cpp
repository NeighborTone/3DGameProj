#include "FieldComponent.h"

FieldComponent::FieldComponent()
{
	tex.Load("Resource/Texture/w.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(1000,48);
}

void FieldComponent::Draw3D()
{
	mesh.scale.y *= 0.001f;
	mesh.Draw();
}


