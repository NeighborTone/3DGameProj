#include "ToppingComponent.h"

ToppingComponent::ToppingComponent()
{
	tex.Load("Resource/Texture/t.png");
	mesh.CreateSphere(2);
	mesh.GetMaterial().SetTexture(0,&tex);
	data.resize(2);
}

void ToppingComponent::Initialize()
{
	//$Test$
	float i = 0;
	for (auto& it : data)
	{
		it.trans.pos = Pos(0, 4, i);
		it.isArrested = false;
		it.isActive = true;
		i += 50;
	}
	
}

void ToppingComponent::UpDate()
{

}

void ToppingComponent::Draw3D()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		mesh.pos = it.trans.pos;
		mesh.Draw();
	}
}

void ToppingComponent::Draw2D()
{
}


std::vector<ToppingData>& ToppingComponent::GetData()
{
	return data;
}
