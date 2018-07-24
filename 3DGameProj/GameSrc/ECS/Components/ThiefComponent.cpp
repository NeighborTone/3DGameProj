#include "ThiefComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include <iterator>
#include <iostream>
std::unique_ptr<MetaData> ThiefComponent::AddEnemy()
{
	return std::make_unique<MetaData>();
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
		data.at(data.size()-1)->velocity = 2.4f;
		data.at(data.size()-1)->scale = radius_ * 2;
		Random rand;
		const float THETA = rand.GetRand(0.f, 360.0f);	//�o���p�x�����߂�
		constexpr float FIELD_RADIUS = 500;		//�t�B�[���h�̔��a
		data.at(data.size()-1)->pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->pos.y = rand.GetRand(10.0f, 100.0f);
		efHandle = GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->pos));
		GameController::GetParticle().SetAngles(efHandle, Vec3(90, 0, 0));
		GameController::GetParticle().SetScale(efHandle, Vec3(3, 3, 3));
		appSound.PlaySE();
	}
}

void ThiefComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const std::unique_ptr<MetaData> &data)
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
		appSound.UpDate3DSound(Vec3(data.at(data.size() - 1)->pos), Vec3(pos.x, pos.y, pos.z));
	}
}

ThiefComponent::ThiefComponent(const float r):
	cnt(0,1,0,120)
{
	GameController::GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GameController::GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	tex.Load("Resource/UFO_D.png");
	appSound.Load("Resource/Sounds/steam_long.wav",true);
	exproSound.Load("Resource/Sounds/se.ogg", true);
	mesh.Load("Resource/ufo.fbx");
	radius_ = r;
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
		if (e.GetComponent<InputShotComponent>().IsHit(AABB(Pos(it->pos), Scale(it->scale.x * 2.0f, it->scale.y * 0.8f, it->scale.z))))
		{
			efHandle = GameController::GetParticle().Play("expro", Pos(it->pos));
			GameController::GetParticle().SetScale(efHandle, Vec3(6, 6, 6));
			exproSound.PlaySE();
			exproSound.UpDate3DSound(Pos(it->pos), Vec3(listenerPos));
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
			//�Ƃ肠�����Ǐ]������
			Vec3 ret = (trackingTarget - pos);
			ret.Normalize();
			return ret;
		};
			
			it->pos += Tracking(it->pos) * it->velocity;
			//�����̐��������߂�
			if (it->pos.y <= 10)
			{
				it->pos.y = 10;
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
			mesh.scale = it->scale / 10;
			mesh.pos = it->pos;
			tex.Attach(0);
			mesh.Draw();
		}
	}
}

void ThiefComponent::SetTrackingTarget(Pos& target)
{

	trackingTarget = target;
}




const std::vector<std::unique_ptr<MetaData>>& ThiefComponent::GetData() const
{
	return data;
}
