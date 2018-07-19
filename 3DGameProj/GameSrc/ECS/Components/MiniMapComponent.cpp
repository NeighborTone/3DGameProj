#include "MiniMapComponent.h"
#include "ThiefComponent.h"
#include "../../GameController/Helper.hpp"
#include <cmath>
MiniMapComponent::MiniMapComponent()
{
	map.Load("Resource/Texture/map.png");
	enemyIcon.Load("Resource/Texture/enemy.png");
}

const void MiniMapComponent::DrawEnemys(const Entity& e, Entity& player)
{
	for (auto& enemys : e.GetComponent<ThiefComponent>().GetData())
	{
		const float dy = ComAssist::GetPos(player).z - enemys->pos.z;
		const float dx = ComAssist::GetPos(player).x - enemys->pos.x;
		const float rad = atan2(dy, dx);				//出現角度を決定
		float distance = sqrt(dx * dx + dy * dy) / 4;	//プレイヤーと敵の距離を調べる
		if (abs(distance) >= 128) { distance = 128; }	//マップの端を超えないようにする
		enemyIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
		enemyIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
		enemyIcon.pos.z = 0;
		const Vec2 mapCenter(
			Engine::GetWindowSize().x / 2.f - mapRadius,
			-Engine::GetWindowSize().y / 2.f + mapRadius);
		enemyIcon.pos.x += mapCenter.x;
		enemyIcon.pos.y += mapCenter.y;


		enemyIcon.Draw();
	}
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
