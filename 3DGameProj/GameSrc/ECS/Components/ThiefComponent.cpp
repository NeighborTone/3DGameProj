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
	//Test
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		data.emplace_back(AddEnemy());
		data.at(data.size()-1)->isActive = true;
		data.at(data.size()-1)->lifeSpan = 3;
		data.at(data.size()-1)->velocity = 0.4f;
		data.at(data.size()-1)->scale = radius * 2;
		Random rand;
		const float THETA = rand.GetRand(0.f, 360.0f);	//出現角度を決める
		constexpr float FIELD_RADIUS = 500;		//フィールドの半径
		data.at(data.size()-1)->pos.x = cosf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->pos.z = sinf(DirectX::XMConvertToRadians(THETA)) * FIELD_RADIUS;
		data.at(data.size()-1)->pos.y = rand.GetRand(10.0f, 100.0f);
		GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->pos));
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

ThiefComponent::ThiefComponent(const float r)
{
	GameController::GetParticle().AddEffect("app", "Resource/Effect/Appear.efk");
	GameController::GetParticle().AddEffect("expro", "Resource/Effect/testEf.efk");
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	appSound.Load("Resource/Sounds/steam_long.wav",true);
	exproSound.Load("Resource/Sounds/se.ogg", true);
	mesh.GetMaterial().Load("Resource/Shader/hoge.hlsl");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.SetDrawMode(D3D11_CULL_BACK, D3D11_FILL_WIREFRAME);
	mesh.CreateSphere();
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
		if (e.GetComponent<InputShotComponent>().IsHit(AABB(Pos(it->pos), Scale(it->scale / 2))))
		{
			GameController::GetParticle().Play("expro", Pos(it->pos));
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

		auto Tracking = [=](Pos& pos)
		{
			//とりあえずプレイヤーに追従させる
			Vec3 ret = (listenerPos - pos);	
			ret.Normalize();
			return ret;
		};
			
			it->pos += Tracking(it->pos) * it->velocity;
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
			mesh.scale = it->scale;
			mesh.pos = it->pos;
			mesh.Draw();
		}
	}
}
