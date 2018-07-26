#include "TomatoComponent.h"
#include "ThiefComponent.h"
#include <algorithm>
#include <iostream>
void TomatoComponent::Executioners()
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

TomatoComponent::TomatoComponent()
{
	tex.Load("Resource/Texture/t.png");
	mesh.CreateSphere(2);
	mesh.GetMaterial().SetTexture(0,&tex);
}

void TomatoComponent::Initialize()
{
	//$Test$
	data.resize(10);
	float i = -40;
	for (auto& it : data)
	{
		it.id = -1;
		it.trans.pos = Pos(0, 4, i);
		it.state = ToppingData::State::EFFECTIVE;
		i += 20;
	}
	
}

void TomatoComponent::UpDate()
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

void TomatoComponent::Draw3D()
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

const std::vector<ToppingData>& TomatoComponent::GetData() const
{
	return data;
}

void TomatoComponent::ToBeKidnapped(Entity& enemy)
{

	if (data.empty())
	{
		return;

	}
	for (auto& targets : data)
	{
		bool enemyIsFind = false;
		for (auto& enemys : enemy.GetComponent<ThiefComponent>().GetData())
		{
			if (targets.id == enemys->id)
			{
				enemyIsFind = true;
				//無効状態のターゲットを動かす
				if (targets.state == ToppingData::State::INVALID && enemys->state == EnemyData::State::GETAWAY)
				{
					//$Test$
					//敵と距離が近い物を一緒に動かす
					if (abs(enemys->trans.pos.GetDistance(Pos(targets.trans.pos)) <= 15))
					{
						targets.trans.pos = enemys->trans.pos;
						targets.trans.pos.y = 8;
					}
				}
			}
			
		}
		if (!enemyIsFind)
		{
			//無効状態から有効にしたいのだがうまくいかない
			targets.state = ToppingData::State::EFFECTIVE;
			targets.trans.pos.y = 4;
			targets.id = -1;
		}
		//すでに無効になっているものや、死んでいるものはスキップ
		if (targets.state != ToppingData::State::EFFECTIVE)
		{
			continue;
		}
		//敵の視界に入ったらさらわれる
		if (enemy.GetComponent<ThiefComponent>().IsToBeInRange(targets.sphere.Create(targets.trans.pos, 1),targets.id))
		{
			targets.state = ToppingData::State::INVALID;
		}
		
	}
}