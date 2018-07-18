#include "MiniMapComponent.h"

MiniMapComponent::MiniMapComponent()
{
	map.Load("Resource/Texture/map.png");
	enemys.Load("Resource/Texture/enemy.png");
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
	enemys.pos = map.pos;
	enemys.pos.x += 20;
	enemys.Draw();

}
