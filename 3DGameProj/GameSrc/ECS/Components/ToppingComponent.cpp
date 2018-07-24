#include "ToppingComponent.h"

ToppingComponent::ToppingComponent()
{
	tex.Load("Resource/Texture/t.png");
	mesh.CreateSphere(2);
	mesh.GetMaterial().SetTexture(0,&tex);
	data.resize(1);
}

void ToppingComponent::Initialize()
{
	data[0].pos = Pos(0, 4, 0);
}

void ToppingComponent::UpDate()
{
}

void ToppingComponent::Draw3D()
{
	mesh.pos = data[0].pos;
	mesh.Draw();
}

void ToppingComponent::Draw2D()
{
}

std::vector<MetaData>& ToppingComponent::GetData()
{
	return data;
}
