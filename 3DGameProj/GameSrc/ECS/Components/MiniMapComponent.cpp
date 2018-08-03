#include "MiniMapComponent.h"
#include "ThiefComponent.h"
#include "TomatoComponent.h"
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
	//�}�b�v�̒��S�ʒu
	const Vec2 mapCenter(Engine::GetWindowSize().x / 2.f - MapRadius, -Engine::GetWindowSize().y / 2.f + MapRadius);
	if (e.HasComponent<TomatoComponent>())
	{
		for (auto& toppings : e.GetComponent<TomatoComponent>().GetData())
		{
			const float dy = ComAssist::GetPos(player).z - toppings.trans.pos.z;
			const float dx = ComAssist::GetPos(player).x - toppings.trans.pos.x;
			const float rad = atan2(dy, dx);				//�p�x������
			float distance = hypot(dx, dy) / 4;			//�v���C���[�ƓG�̋����𒲂ׂ�
			if (abs(distance) >= MapRadius) { distance = MapRadius; }	//�}�b�v�̒[�𒴂��Ȃ��悤�ɂ���
			toppingIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			toppingIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
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
			const float rad = atan2(dy, dx);				//�p�x������
			float distance = hypot(dx, dy) / 4;	//�v���C���[�Ƃ̋����𒲂ׂ�
			if (abs(distance) >= MapRadius) { distance = MapRadius; }	//�}�b�v�̒[�𒴂��Ȃ��悤�ɂ���
			enemyIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			enemyIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance;
			enemyIcon.pos.x += mapCenter.x;
			enemyIcon.pos.y += mapCenter.y;
			enemyIcon.color.a = 0.8f;
			enemyIcon.Draw();
		}
	}
	
}

void MiniMapComponent::Draw2D()
{
	map.pos.x = Engine::GetWindowSize().x / 2.f - MapRadius;
	map.pos.y = -Engine::GetWindowSize().y / 2.f + MapRadius;
	map.Draw();
}
