#include "MiniMapComponent.h"
#include "UFOComponent.h"
#include "TomatoComponent.h"
#include "../../GameController/Helper.hpp"
#include <cmath>
MiniMapComponent::MiniMapComponent()
{
	map.Load("Resource/Texture/map.png");
	enemyIcon.Load("Resource/Texture/enemy.png");
	targetIcon.Load("Resource/Texture/topping.png");
}

void MiniMapComponent::DrawEntityes(const Entity& e, Entity& player)
{
	//�}�b�v�̒��S�ʒu
	const Vec2 mapCenter(MapRadius* 2.2f, -MapRadius * 2.2f);
	if (e.HasComponent<TomatoComponent>())
	{
		for (auto& tomatos : e.GetComponent<TomatoComponent>().GetData())
		{
			const float dy = ComAssist::GetPos(player).z - tomatos.trans.pos.z;
			const float dx = ComAssist::GetPos(player).x - tomatos.trans.pos.x;
			const float rad = atan2(dy, dx);				//�p�x������
			float distance = hypot(dx, dy) / 4;			//�v���C���[�ƓG�̋����𒲂ׂ�
			if (abs(distance) >= MapRadius) { distance = MapRadius; }	//�}�b�v�̒[�𒴂��Ȃ��悤�ɂ���
			targetIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance * ExpansionRate;
			targetIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance * ExpansionRate;
			targetIcon.pos.x += mapCenter.x;
			targetIcon.pos.y += mapCenter.y;
			targetIcon.Draw();
		}
	}
	if (e.HasComponent<UFOComponent>())
	{
		for (auto& enemys : e.GetComponent<UFOComponent>().GetData())
		{
			const float dy = ComAssist::GetPos(player).z - enemys->trans.pos.z;
			const float dx = ComAssist::GetPos(player).x - enemys->trans.pos.x;
			const float rad = atan2(dy, dx);				//�p�x������
			float distance = hypot(dx, dy) / 4;	//�v���C���[�Ƃ̋����𒲂ׂ�
			if (abs(distance) >= MapRadius) { distance = MapRadius; }	//�}�b�v�̒[�𒴂��Ȃ��悤�ɂ���
			enemyIcon.pos.x = -cosf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance * ExpansionRate;
			enemyIcon.pos.y = -sinf(rad + DirectX::XMConvertToRadians(ComAssist::GetAngles(player).y)) * distance * ExpansionRate;
			enemyIcon.pos.x += mapCenter.x;
			enemyIcon.pos.y += mapCenter.y;
			enemyIcon.color.a = 0.8f;
			enemyIcon.Draw();
		}
	}
}

void MiniMapComponent::Draw2D()
{
	map.pos.x = MapRadius * 2.2f;
	map.pos.y = -MapRadius * 2.2f;
	map.Draw();
}
