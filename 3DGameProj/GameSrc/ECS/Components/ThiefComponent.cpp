#include "ThiefComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include "../Components/TomatoComponent.h"
#include "../../Utilitys/Randam.hpp"
#include <iterator>
#include <iostream>
#include <algorithm>

long long ThiefComponent::id_ = 0;

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
		data.at(data.size() - 1)->state = EnemyData::State::TRACKING;
		data.at(data.size() - 1)->lifeSpan = 3;
		data.at(data.size() - 1)->trans.velocity = 2.4f;
		data.at(data.size() - 1)->trans.scale = RADIUS * 2;
		Random rand;
		const float THETA = rand.GetRand(0.f, 360.0f);	//出現角度を決める
		constexpr float FIELD_RADIUS = 500;		//フィールドの半径
		data.at(data.size() - 1)->trans.pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size() - 1)->trans.pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size() - 1)->trans.pos.y = rand.GetRand(20.0f, 100.0f);
		data.at(data.size() - 1)->trackingTarget = Pos(0, 0, 0);
		data.at(data.size() - 1)->id = id_;
		std::cout << id_ << std::endl;
		efHandle = GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->trans.pos));
		GameController::GetParticle().SetAngles(efHandle, Vec3(90, 0, 0));
		GameController::GetParticle().SetScale(efHandle, Vec3(3, 3, 3));
		appSound.PlaySE();
		++id_;
	}
}

void ThiefComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const std::unique_ptr<EnemyData> &data)
	{
		constexpr float FieldOut = 1000;
		return data->state == EnemyData::State::DEATH || abs(data->trans.pos.x) >= FieldOut || abs(data->trans.pos.z) >= FieldOut;
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

ThiefComponent::ThiefComponent() :
	cnt(0, 1, 0, 120)
{
	GameController::GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GameController::GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	tex.Load("Resource/UFO_D.png");
	appSound.Load("Resource/Sounds/steam_long.wav", true);
	exproSound.Load("Resource/Sounds/se.ogg", true);
	model.Load("Resource/ufo.fbx");
}

void ThiefComponent::Damaged(Entity& e)
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
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

bool ThiefComponent::IsToBeInRange(Sphere& sphere,long long& id_)
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
		if (Collison::SphereAABBCollision(sphere, it->aabb.Create(
			it->trans.pos - 5, 
			Scale(it->trans.scale.x * 1.0f, it->trans.scale.y * 3.3f, it->trans.scale.z * 1.0f))))
		{
			//当たった敵と同じIDにする
			id_ = it->id;
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
	id_ = 0;
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
			it->trans.pos.z += it->trans.velocity.z * -1;
			it->trans.pos.x += it->trans.velocity.x * -1;
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
	if (!target.HasComponent<TomatoComponent>())
	{
		return;
	}
	if (target.GetComponent<TomatoComponent>().GetData().empty())
	{
		return;
	}
	auto& targets = target.GetComponent<TomatoComponent>().GetData();
	std::vector<std::pair<float, Pos>> dist;
	dist.resize(targets.size());
	dist.shrink_to_fit();
	for (auto& it : data)
	{
		if (it->state == EnemyData::State::TRACKING)
		{
			for (size_t i = 0; i < targets.size(); ++i)
			{
				if (targets[i].state == ToppingData::State::INVALID)
				{
#undef min	//$Test$
#undef max	//無効なターゲットも追跡してしまうので無効なものは遠くにしておく
					constexpr float Max = std::numeric_limits<float>::max();
					dist[i].first = Max;
					dist[i].second = Pos(Max, Max, Max);
					continue;
				}
				//複数の有効なターゲットとの距離を測る
				dist[i].first = abs(it->trans.pos.GetDistance(Pos(targets[i].trans.pos)));
				//座標の保存
				dist[i].second = targets[i].trans.pos;
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
