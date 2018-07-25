#include "ThiefComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include "../Components/ToppingComponent.h"
#include "../../Utilitys/Randam.hpp"
#include <iterator>
#include <iostream>
#include <algorithm>

std::unique_ptr<EnemyData> ThiefComponent::AddEnemy()
{
	return std::make_unique<EnemyData>();
}

void ThiefComponent::LifeCheck()
{
	for (auto& it : data)
	{
		if (it->lifeSpan <= 0)
		{
			it->state = EnemyData::State::DEATH;
		}
	}
}

void ThiefComponent::Create()
{
	//$Test$
	if (cnt.GetCurrentCount() > 120)
	{
		data.emplace_back(AddEnemy());
		data.at(data.size()-1)->state = EnemyData::State::TRACKING;
		data.at(data.size()-1)->lifeSpan = 3;
		data.at(data.size()-1)->trans.velocity = 2.4f;
		data.at(data.size()-1)->trans.scale = RADIUS * 2;
		Random rand;
		const float THETA = rand.GetRand(0.f, 360.0f);	//出現角度を決める
		constexpr float FIELD_RADIUS = 500;		//フィールドの半径
		data.at(data.size()-1)->trans.pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->trans.pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->trans.pos.y = rand.GetRand(20.0f, 100.0f);
		data.at(data.size() - 1)->trackingTarget = Pos(0, 0, 0);
		efHandle = GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->trans.pos));
		GameController::GetParticle().SetAngles(efHandle, Vec3(90, 0, 0));
		GameController::GetParticle().SetScale(efHandle, Vec3(3, 3, 3));
		appSound.PlaySE();
	}
}

void ThiefComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const std::unique_ptr<EnemyData> &data)
	{
		return data->state == EnemyData::State::DEATH;
	}),
		std::end(data));
}


void ThiefComponent::SetListenerPos(Pos&& pos)
{
	if (!data.empty())
	{
		listenerPos = pos;	
		appSound.UpDate3DSound(Vec3(data.at(data.size() - 1)->trans.pos), Vec3(pos.x, pos.y, pos.z));
	}
}

ThiefComponent::ThiefComponent():
	cnt(0,1,0,120)
{
	GameController::GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GameController::GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	tex.Load("Resource/UFO_D.png");
	appSound.Load("Resource/Sounds/steam_long.wav",true);
	exproSound.Load("Resource/Sounds/se.ogg", true);
	model.Load("Resource/ufo.fbx");
}

void ThiefComponent::Damaged(Entity& e)
{
	if (data.empty())
	{
		return;
	}
	for (auto& it :data)
	{
		if (it->state == EnemyData::State::DEATH)
		{
			continue;
		}
		if (e.GetComponent<InputShotComponent>().IsHit(it->aabb.Create(it->trans.pos, Scale(it->trans.scale.x * 2.1f, it->trans.scale.y * 0.8f, it->trans.scale.z))))
		{
			efHandle = GameController::GetParticle().Play("expro", Pos(it->trans.pos));
			GameController::GetParticle().SetScale(efHandle, Vec3(6, 6, 6));
			exproSound.PlaySE();
			exproSound.UpDate3DSound(Pos(it->trans.pos), Vec3(listenerPos));
			--it->lifeSpan;
		}
	
	}
}

bool ThiefComponent::IsToBeInRange(Sphere& sphere)
{
	if (data.empty())
	{
		return false;
	}
	for (auto& it : data)
	{
		if (it->state != EnemyData::State::TRACKING)
		{
			continue;
		}
		if (Collison::SphereAABBCollision(sphere, it->aabb.Create(it->trans.pos - 5, Scale(it->trans.scale.x * 2.0f, it->trans.scale.y * 1.3f, it->trans.scale.z * 2))))
		{
			it->state = EnemyData::State::GETAWAY;
			return true;
		}
	}
	return false;
}

void ThiefComponent::Initialize()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		it->state = EnemyData::State::DEATH;
	}
	Executioners();
}

void ThiefComponent::UpDate()
{
	++cnt;
	Create();
	if (data.empty())
	{
		return;
	}
	LifeCheck();
	//$Test$
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::TRACKING)
		{
			//追従させる
			Vec3 ret = (it->trackingTarget - it->trans.pos);
			ret.Normalize();

			it->trans.pos += ret * it->trans.velocity;
			//高さの制限を決める
			if (it->trans.pos.y <= 10)
			{
				it->trans.pos.y = 10;
			}
		}
		if (it->state == EnemyData::State::GETAWAY)
		{
			//$Test$
			//it->trans.pos.z += it->trans.velocity.z * -1;
		}
	}	
	
	Executioners();
}

void ThiefComponent::Draw3D()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		if (it->state != EnemyData::State::DEATH)
		{
			model.scale = it->trans.scale / 10;	//元のモデルが大きすぎるので
			model.pos = it->trans.pos;
			tex.Attach(0);
			model.Draw();
		}
	}
}

void ThiefComponent::SetTrackingTarget(Entity& target)
{
	if (!target.HasComponent<ToppingComponent>())
	{
		return;
	}
	if (target.GetComponent<ToppingComponent>().GetData().empty())
	{
		return;
	}
	std::vector<std::pair<float,Pos>> dist;
	dist.resize(target.GetComponent<ToppingComponent>().GetData().size());
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::TRACKING)
		{
			for (size_t i = 0; i < target.GetComponent<ToppingComponent>().GetData().size(); ++i)
			{
				if (target.GetComponent<ToppingComponent>().GetData()[i].state == ToppingData::State::EFFECTIVE)
				{
					//複数のターゲットとの距離を測る
					dist[i].first = abs(it->trans.pos.GetDistance(target.GetComponent<ToppingComponent>().GetData()[i].trans.pos));
					//座標の保存
					dist[i].second = target.GetComponent<ToppingComponent>().GetData()[i].trans.pos;
				}
				
			}
			//自分から見て一番近いものを追う
			std::sort(std::begin(dist), std::end(dist), ComAssist::comp);
			it->trackingTarget = dist[0].second;
		}
	}
	
}

const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::GetData() const
{
	return data;
}
