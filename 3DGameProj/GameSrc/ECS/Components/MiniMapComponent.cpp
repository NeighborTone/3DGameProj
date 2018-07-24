#include "MiniMapComponent.h"
#include "ThiefComponent.h"
#include "ToppingComponent.h"
#include "../../GameController/Helper.hpp"
#include <cmath>
MiniMapComponent::MiniMapComponent()
{
	map.Load("Resource/Texture/map.png");
	enemyIcon.Load("Resource/Texture/enemy.png");
	toppingIcon.Load("Resource/Texture/topping.png");
}

const void MiniMapComponent::DrawEntityes(const Entity& e, Entity& player)
{
	if (e.HasComponent<ToppingComponent>())
	{
		for (auto& toppings : e.GetComponent<ToppingComponent>().GetData())
		{
			const float dy = ComAssist::GetPos(player).z - toppings.trans.pos.z;
			const float dx = ComAssist::GetPos(player).x - toppings.trans.pos.x;
			const float rad = atan2(dy, dx);				//出現角度を決定
			float distance = hypot(dx, dy) / 4;				//プレイヤーと敵の距離を調べる
			if (abs(distance) >= 128) { distance = 128; }	//マップの端を超えないようにする
			toppingIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			toppingIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			toppingIcon.pos.z = 1;
			const Vec2 mapCenter(Engine::GetWindowSize().x / 2.f - mapRadius, -Engine::GetWindowSize().y / 2.f + mapRadius);
			toppingIcon.pos.x += mapCenter.x;
			toppingIcon.pos.y += mapCenter.y;


			toppingIcon.Draw();
		}
	}
	if (e.HasComponent<ThiefComponent>())
	{
		for (auto& enemys : e.GetComponent<ThiefComponent>().GetData())
		{
			const float dy = ComAssist::GetPos(player).z - enemys->trans.pos.z;
			const float dx = ComAssist::GetPos(player).x - enemys->trans.pos.x;
			const float rad = atan2(dy, dx);				//出現角度を決定
			float distance = hypot(dx, dy) / 4;	//プレイヤーとの距離を調べる
			if (abs(distance) >= 128) { distance = 128; }	//マップの端を超えないようにする
			enemyIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			enemyIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			enemyIcon.pos.z = 0;
			const Vec2 mapCenter(Engine::GetWindowSize().x / 2.f - mapRadius, -Engine::GetWindowSize().y / 2.f + mapRadius);
			enemyIcon.pos.x += mapCenter.x;
			enemyIcon.pos.y += mapCenter.y;


			enemyIcon.Draw();
		}
	}
	
}

const void MiniMapComponent::DrawTopping(const Entity& topping_, Entity & player)
{
	
}

void MiniMapComponent::Initialize()
{

	
}

void MiniMapComponent::UpDate()
{

}

void MiniMapComponent::Draw2D()
{
	map.pos.x = Engine::GetWindowSize().x / 2.f - mapRadius;
	map.pos.y = -Engine::GetWindowSize().y / 2.f + mapRadius;
	map.Draw();
	

}
