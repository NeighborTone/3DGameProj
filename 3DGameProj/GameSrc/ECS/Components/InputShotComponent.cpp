#include"InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include <iostream>
InputShotComponent::InputShotComponent(const float speed, const int maxNum, const float radius) :
	speed_(speed)
{
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	shots.resize(maxNum);
	for (auto& it : shots)
	{
		it.mesh.GetMaterial().Load("Resource/Shader/shot.hlsl");
		it.mesh.GetMaterial().SetTexture(0, &tex);
		it.radius = radius;
		it.mesh.CreateSphere(it.radius*2);
	}
}

void InputShotComponent::Initialize()
{
	for (auto& it : shots)
	{
		it.deathTime = 0;
		it.isActive = false;
	}
}

void InputShotComponent::UpDate()
{
	for (auto& it : shots)
	{
		if (it.isActive)
		{
			it.mesh.pos += it.velocity;
			++it.deathTime;
		}
		if (it.deathTime > 100 && it.isActive)
		{
			it.deathTime = 0;
			it.isActive = false;
		}
	}
}

void InputShotComponent::Draw3D()
{
	for (auto& it : shots)
	{
		if (it.isActive)
		{
			it.mesh.Draw();
		}
	}
}

void InputShotComponent::Shot(TransformComponent&& trans)
{
	bool isShot = Mouse::L_On() % 6 == 1;

	for (auto& it : shots)
	{
		if (isShot && !it.isActive)
		{
			//いったんセット
			it.mesh.pos = trans.pos;
			//弾の射出方向を決める。90度ずれてしまうのでオフセットする
			it.velocity.x = cosf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.velocity.y = sinf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.velocity.z = cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * sinf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * speed_;
			it.isActive = true;
			//カメラとかぶるのでちょっと前に出す
			it.mesh.pos += (it.velocity  * 1.2f);
			break;
		}
	}
}

bool InputShotComponent::IsHit(AABB&& sphere)
{
	for (auto& it : shots)
	{
		if (!it.isActive)
		{
			continue;
		}
		if (Collison::SegmentAABBCollision(Vec3(it.mesh.pos), Vec3(it.mesh.pos + it.velocity), AABB(sphere)))
		{
			it.deathTime = 0;
			it.isActive = false;
			return true;
		}
	
	}
	return false;
}

const std::vector<InputShotComponent::Shots>& InputShotComponent::GetShots() const
{
	return shots;
}
