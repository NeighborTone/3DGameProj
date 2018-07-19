#include "MiniMapComponent.h"
#include "ThiefComponent.h"
#include "../../GameController/Helper.hpp"
#include <cmath>
MiniMapComponent::MiniMapComponent()
{
	map.Load("Resource/Texture/map.png");
	enemyIcon.Load("Resource/Texture/enemy.png");
}

void MiniMapComponent::DrawEnemys(Entity& e, Entity& player)
{
	for (auto& enemys : e.GetComponent<ThiefComponent>().GetData())
	{
		const float dy = ComAssist::GetPos(player).z - enemys->pos.z;
		const float dx = ComAssist::GetPos(player).x - enemys->pos.x;
		const float rad = atan2(dy, dx);//出現角度を決定
		const float distance = sqrt(dx*dx + dy * dy) / 4;	//プレイヤーと敵の距離
		enemyIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
		enemyIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
		enemyIcon.pos.z = 0;
		enemyIcon.pos.x += 512;
		enemyIcon.pos.y -= 298;
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
	map.pos.x = Engine::GetWindowSize().x / 2.f - 128;
	map.pos.y = -Engine::GetWindowSize().y / 2.f + 128;
	map.Draw();
	

}
