#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"

//Entityの制御を行うクラスです
class GameController
{
private:
	enum GameGroup : std::size_t
	{
		ALWAYS,	//ゲームの状態に関わらず常に更新と描画を行うグループ
		GAME,		//ゲーム中に更新を行うグループ
		END			//未定
	};

	EntityManager entityManager;

	Entity& gameMaster;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& enemy;
	Entity& field;
	Entity& canvas;
	Entity& topping;
public:
	static Particle& GetParticle();	
	GameController();
	~GameController() = default;
	void CollisionEvent();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};