#include "FieldComponent.h"

FieldComponent::FieldComponent()
{
	tex.Load("Resource/Texture/w.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(1,26);
}

void FieldComponent::Draw3D()
{
	mesh.scale = 1000;
	mesh.scale.y = 1;
	mesh.Draw();
}


