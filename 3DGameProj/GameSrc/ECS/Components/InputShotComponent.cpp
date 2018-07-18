#include"InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include <iostream>
InputShotComponent::InputShotComponent(const float speed, const int maxNum, const float radius) :
	speed_(speed)
{
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	mesh.GetMaterial().Load("Resource/Shader/shot.hlsl");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(radius * 2);
	shots.resize(maxNum);
	for (auto& it : shots)
	{
		it.scale = radius * 2;
		it.radius = radius;
	}
}

void InputShotComponent::Initialize()
{
	for (auto& it : shots)
	{
		it.lifeSpan = 0;
		it.isActive = false;
	}
}

void InputShotComponent::UpDate()
{
	for (auto& it : shots)
	{
		if (it.isActive)
		{
			it.pos += it.velocity;
			++it.lifeSpan;
		}
		if (it.lifeSpan > 100 && it.isActive)
		{
			it.lifeSpan = 0;
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
			mesh.pos = it.pos;
			mesh.scale = it.scale;
			mesh.Draw();
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
			it.pos = trans.pos;
			//弾の射出方向を決める。90度ずれてしまうのでオフセットする
			it.velocity.x = cosf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.velocity.y = sinf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.velocity.z = cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * sinf(DirectX::XMConvertToRadians(-trans.angle.y + 90)) * speed_;
			it.isActive = true;
			//カメラとかぶるのでちょっと前に出す
			it.pos += (it.velocity  * 0.5f);
			break;
		}
	}
}

bool InputShotComponent::IsHit(AABB&& aabb)
{
	for (auto& it : shots)
	{
		if (!it.isActive)
		{
			continue;
		}
		if (Collison::SegmentAABBCollision(Vec3(it.pos), Vec3(it.pos + it.velocity), AABB(aabb)))
		{
			it.lifeSpan = 0;
			it.isActive = false;
			return true;
		}
	}
	return false;
}

