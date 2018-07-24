#include "ThiefComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include "../Components/ToppingComponent.h"
#include <iterator>
#include <iostream>
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
			it->isActive = false;
		}
	}
}

void ThiefComponent::Create()
{
	//$Test$
	if (cnt.GetCurrentCount() > 120)
	{
		data.emplace_back(AddEnemy());
		data.at(data.size()-1)->isActive = true;
		data.at(data.size()-1)->lifeSpan = 3;
		data.at(data.size()-1)->trans.velocity = 2.4f;
		data.at(data.size()-1)->trans.scale = RADIUS * 2;
		Random rand;
		const float THETA = rand.GetRand(0.f, 360.0f);	//oŒ»Šp“x‚ðŒˆ‚ß‚é
		constexpr float FIELD_RADIUS = 500;		//ƒtƒB[ƒ‹ƒh‚Ì”¼Œa
		data.at(data.size()-1)->trans.pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->trans.pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->trans.pos.y = rand.GetRand(10.0f, 100.0f);
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
		return !data->isActive;
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
		if (!it->isActive)
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

void ThiefComponent::Initialize()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		it->isActive = false;
	}
	isAbduction = false;
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
		if (it->isActive)
		{

		auto Tracking = [=](Pos& pos)
		{
			//‚Æ‚è‚ ‚¦‚¸’Ç]‚³‚¹‚é
			Vec3 ret = (trackingTarget[0] - pos);
			ret.Normalize();
			return ret;
		};
			
			it->trans.pos += Tracking(it->trans.pos) * it->trans.velocity;
			//‚‚³‚Ì§ŒÀ‚ðŒˆ‚ß‚é
			if (it->trans.pos.y <= 10)
			{
				it->trans.pos.y = 10;
			}
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
		if (it->isActive)
		{
			model.scale = it->trans.scale / 10;
			model.pos = it->trans.pos;
			tex.Attach(0);
			model.Draw();
		}
	}
}

void ThiefComponent::SetTrackingTarget(Entity& target)
{
	trackingTarget.resize(target.GetComponent<ToppingComponent>().GetData().size());
	for (auto& toppings : target.GetComponent<ToppingComponent>().GetData())
	{
		for (auto& targets : trackingTarget)
		{
			targets = toppings.trans.pos;
		}
		
	}
	
}

const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::GetData() const
{
	return data;
}
