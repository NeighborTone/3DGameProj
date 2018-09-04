#include "TomatoComponent.h"
#include "UFOComponent.h"
#include <algorithm>
#include <iostream>
void TomatoComponent::Refresh()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const TomatoData &data)
	{
		return data.state == TomatoData::State::DEATH || abs(data.trans.pos.x) >= FieldOut || abs(data.trans.pos.z) >= FieldOut;
	}),
		std::end(data));
	data.shrink_to_fit();
}

TomatoComponent::TomatoComponent()
{
	tex.Load("Resource/Texture/t.png");
	mesh.CreateSphere(4);
	mesh.GetMaterial().SetTexture(0,&tex);
}

void TomatoComponent::Initialize()
{
	data.resize(10);
	float i = 0;
	for (auto& it : data)
	{
		Random rand;
		const float THETA = 36 * i;	//出現角度を決める
		const float APP_RADIUS = 160;		//半径
		it.trans.pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * APP_RADIUS;
		it.trans.pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * APP_RADIUS;
		it.trans.pos.y = OnGround;
		it.id = -1;
		it.state = TomatoData::State::EFFECTIVE;
		++i;
	}
}

void TomatoComponent::UpDate()
{
	if (data.empty())
	{
		return;
	}
	Refresh();
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

void TomatoComponent::GameOver(GameState& state) const
{
	if (data.empty())
	{
		state = GameState::END;
	}
}

const std::vector<TomatoData>& TomatoComponent::GetData() const
{
	return data;
}

void TomatoComponent::ToBeKidnapped(Entity& enemy)
{
	auto& enemys = enemy.GetComponent<UFOComponent>().GetData();
	if (data.empty() ||
		enemys.data() == nullptr ||
		data.data() == nullptr)
	{
		return;

	}
	for (auto& targets : data)
	{
		bool enemyIsFind = false;
		for (auto& enemysIt : enemys)
		{
			if (targets.id == enemysIt->id)
			{
				enemyIsFind = true;
				//無効状態のターゲットを動かす
				if (targets.state == TomatoData::State::INVALID && enemysIt->state == EnemyData::State::GETAWAY)
				{
					//敵と距離が近い物を一緒に動かす
					if (abs(enemysIt->trans.pos.GetDistance(Pos(targets.trans.pos)) <= 15))
					{
						targets.trans.pos = enemysIt->trans.pos;
						targets.easeSucked.Run(Easing::QuadIn,50);
						targets.trans.pos.y = targets.easeSucked.GetVolume(OnGround, enemysIt->trans.pos.y - 4);
					}
				}
			}
		}
		if (!enemyIsFind)
		{
			targets.state = TomatoData::State::EFFECTIVE;
			targets.easeSucked.Reset();
			targets.trans.pos.y = OnGround;
			targets.id = -1;
		}
		//すでに無効になっているものや、死んでいるものはスキップ
		if (targets.state != TomatoData::State::EFFECTIVE)
		{
			continue;
		}
		//敵の視界に入ったらさらわれる
		if (enemy.GetComponent<UFOComponent>().IsToBeInRange(targets.sphere.Create(targets.trans.pos, 1),targets.id))
		{
			targets.state = TomatoData::State::INVALID;
		}
	}
}