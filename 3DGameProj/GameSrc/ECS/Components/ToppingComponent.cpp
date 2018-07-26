#include "ToppingComponent.h"
#include "ThiefComponent.h"
#include <algorithm>
void ToppingComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const ToppingData &data)
	{
		constexpr float FieldOut = 950;
		return data.state == ToppingData::State::DEATH || abs(data.trans.pos.x) >= FieldOut || abs(data.trans.pos.z) >= FieldOut;
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
	float i = -40;
	for (auto& it : data)
	{
		it.trans.pos = Pos(0, 4, i);
		it.state = ToppingData::State::EFFECTIVE;
		i += 20;
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

const std::vector<ToppingData>& ToppingComponent::GetData() const
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
		for (auto& enemys : enemy.GetComponent<ThiefComponent>().GetData())
		{
			if (it.state == ToppingData::State::INVALID && enemys->state == EnemyData::State::GETAWAY)
			{
				//$Test$
				//“G‚Æ‹——£‚ª‹ß‚¢•¨‚ðˆê‚É“®‚©‚·
				if (abs(enemys->trans.pos.GetDistance(Pos(it.trans.pos)) <= 15))
				{
					it.trans.pos = enemys->trans.pos;
					it.trans.pos.y = 8;
				}
			}
		}
		if (it.state != ToppingData::State::EFFECTIVE)
		{
			continue;
		}
		if (enemy.GetComponent<ThiefComponent>().IsToBeInRange(it.sphere.Create(it.trans.pos, 1)))
		{
			it.state = ToppingData::State::INVALID;
		}
	}
}