#include "ToppingComponent.h"
#include "ThiefComponent.h"
void ToppingComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const ToppingData &data)
	{
		return data.state == ToppingData::State::DEATH;
	}),
		std::end(data));
	data.shrink_to_fit();
}

ToppingComponent::ToppingComponent()
{
	tex.Load("Resource/Texture/t.png");
	mesh.CreateSphere(2);
	mesh.GetMaterial().SetTexture(0,&tex);
}

void ToppingComponent::Initialize()
{
	//$Test$
	data.resize(10);
	float i = 0;
	for (auto& it : data)
	{
		it.trans.pos = Pos(0, 4, i);
		it.state = ToppingData::State::EFFECTIVE;
		i += 10;
	}
	
}

void ToppingComponent::UpDate()
{
	if (data.empty())
	{
		return;
	}
	//$Test$
	if (KeyBoard::Down(KeyBoard::Key::KEY_V))
	{
		data[0].state = ToppingData::State::DEATH;
	}
	Executioners();
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

void ToppingComponent::ToBeKidnapped(Entity& enemy)
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		if (it.state != ToppingData::State::EFFECTIVE)
		{
			continue;
		}
		if (enemy.GetComponent<ThiefComponent>().IsToBeInRange(it.sphere.Create(it.trans.pos, 10)))
		{
			it.state = ToppingData::State::INVALID;

		}

	}
}
