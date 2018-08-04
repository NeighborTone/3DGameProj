#include"InputShotComponent.h"
#include "../../GameController/Helper.hpp"
#include <iostream>
InputShotComponent::InputShotComponent(const float speed, const int maxNum, const float radius) :
	speed_(speed)
{
	tex.Load("Resource/Texture/shot.png");
	mesh.GetMaterial().SetTexture(0, &tex);
	mesh.CreateSphere(radius * 2);
	shots.resize(maxNum);
	for (auto& it : shots)
	{
		it.trans.scale = radius * 2;
	}
}

void InputShotComponent::Initialize()
{
	for (auto& it : shots)
	{
		it.cnt = 0;
		it.isActive = false;
	}
}

void InputShotComponent::UpDate()
{
	for (auto& it : shots)
	{
		if (it.isActive)
		{
			it.trans.pos += it.trans.velocity;
			++it.cnt;
		}
		if (it.cnt > KillTime && it.isActive)
		{
			it.cnt = 0;
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
			mesh.pos = it.trans.pos;
			mesh.scale = it.trans.scale;
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
			it.trans.pos = trans.pos;
			//弾の射出方向を決める。90度ずれてしまうのでオフセットする
			static constexpr float DirOffSet = 90;
			it.trans.velocity.x = cosf(DirectX::XMConvertToRadians(-trans.angle.y + DirOffSet)) * cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.trans.velocity.y = sinf(DirectX::XMConvertToRadians(-trans.angle.x)) * speed_;
			it.trans.velocity.z = cosf(DirectX::XMConvertToRadians(-trans.angle.x)) * sinf(DirectX::XMConvertToRadians(-trans.angle.y + DirOffSet)) * speed_;
			it.isActive = true;
			//カメラとかぶるのでちょっと前に出す
			it.trans.pos += (it.trans.velocity  * 0.2f);
			break;
		}
	}
}

bool InputShotComponent::IsHit(AABB& aabb)
{
	for (auto& it : shots)
	{
		if (!it.isActive)
		{
			continue;
		}
		if (Collison::SegmentAABBCollision(Vec3(it.trans.pos), Vec3(it.trans.pos + it.trans.velocity), AABB(aabb)))
		{
			it.cnt = 0;
			it.isActive = false;
			return true;
		}
	}
	return false;
}

