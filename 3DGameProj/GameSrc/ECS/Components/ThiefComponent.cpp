#include "ThiefComponent.h"
#include "InputShotComponent.h"
#include "../../GameController/Helper.hpp"
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
		if (it->life <= 0)
		{
			it->isActive = false;
		}
	}
}

void ThiefComponent::Create()
{
	//Test
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		data.emplace_back(AddEnemy());
		Random rand;
		data.at(data.size()-1)->mesh.GetMaterial().Load("Resource/Shader/hoge.hlsl");
		data.at(data.size()-1)->mesh.GetMaterial().SetTexture(0, &tex);
		data.at(data.size()-1)->mesh.CreateSphere();
		data.at(data.size()-1)->isActive = true;
		data.at(data.size()-1)->life = 3;
		data.at(data.size()-1)->velocity = 0.4f;
		data.at(data.size()-1)->mesh.scale = radius * 2;
		const float theta = rand.GetRand(0.f, 360.0f);	//出現角度を決める
		constexpr float FIELD_RADIUS = 500;		//フィールドの半径
		data.at(data.size()-1)->mesh.pos.x = cosf(DirectX::XMConvertToRadians(theta)) * FIELD_RADIUS;
		data.at(data.size()-1)->mesh.pos.z = sinf(DirectX::XMConvertToRadians(theta)) * FIELD_RADIUS;
		data.at(data.size()-1)->mesh.pos.y = rand.GetRand(10.0f, 100.0f);

		GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->mesh.pos));
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
		pos_ = pos;	
		appSound.UpDate3DSound(Vec3(data.at(data.size() - 1)->mesh.pos), Vec3(pos.x, pos.y, pos.z));
	}
}

ThiefComponent::ThiefComponent(const float r)
{
	GameController::GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GameController::GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	appSound.Load("Resource/Sounds/steam_long.wav",true);
	exproSound.Load("Resource/Sounds/se.ogg", true);
	radius = r;
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
		if (e.GetComponent<InputShotComponent>().IsHit(AABB(Pos(it->mesh.pos), Scale(it->mesh.scale / 2))))
		{
			GameController::GetParticle().Play("expro", Pos(it->mesh.pos));
			exproSound.PlaySE();
			exproSound.UpDate3DSound(Pos(it->mesh.pos), Vec3(pos_.x, pos_.y, pos_.z));
			--it->life;
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
	Executioners();
}

void ThiefComponent::UpDate()
{
	Create();
	if (data.empty())
	{
		return;
	}
	LifeCheck();
	
	//Test
	for (auto& it : data)
	{
		if (it->isActive)
		{

		auto Tracking = [=](Pos &pos) {
			Vec3 ret = (pos_ - pos);
			ret.Normalize();
			return ret;
		};
			
			it->mesh.pos += Tracking(it->mesh.pos) * it->velocity;
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
			it->mesh.Draw();
		}
	}
}

const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::Get() const
{
	return data;
}
