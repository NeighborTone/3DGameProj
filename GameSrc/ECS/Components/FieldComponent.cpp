#include "FieldComponent.h"

FieldComponent::FieldComponent()
{
	tex.Load("Resource/Texture/w.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(1000,48);
	mesh.GetMaterial().Load("Resource/Shader/mesh_l.hlsl");
	mesh.SetDrawMode(D3D11_CULL_BACK,D3D11_FILL_WIREFRAME);
	directionalLight.type = Light::Type::Directional;
}

void FieldComponent::Initialize()
{
	AsetManager::GetParticle().Stop(efHandle);
	efHandle = AsetManager::GetParticle().Play("field", Pos(0, 0, 0));	
}

void FieldComponent::Draw3D()
{
	directionalLight.pos = Vec3(0.0f, 100.0f, -500.0f);
	static float y = 0;
	++y;
	directionalLight.color = Float4(0, 0, 1, 1);
	directionalLight.angles = Vec3(-15.0f, y, 0.0f);
	directionalLight.intensity = 5.f;
	directionalLight.range = 10;
	directionalLight.Draw();
	mesh.scale.y *= 0.001f;
	mesh.Draw();
}


