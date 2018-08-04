#include "FieldComponent.h"

FieldComponent::FieldComponent()
{
	tex.Load("Resource/Texture/w.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(1000,48);
	mesh.SetDrawMode(D3D11_CULL_BACK,D3D11_FILL_WIREFRAME);
}

void FieldComponent::Initialize()
{
	AsetManager::GetParticle().Stop(efHandle);
	efHandle = AsetManager::GetParticle().Play("field", Pos(0, 0, 0));	
}

void FieldComponent::Draw3D()
{
	mesh.scale.y *= 0.001f;
	mesh.Draw();
}


