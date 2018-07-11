#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"

//EntityÇÃêßå‰ÇçsÇ§ÉNÉâÉXÇ≈Ç∑
class GameController
{
private:
	EntityManager entityManager;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	//âº
	Entity& hoge;
	Particle ef;
	SoundEngine::SoundSource sound;
	//
public:
	GameController();
	~GameController();
	void CollisionEvent();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};