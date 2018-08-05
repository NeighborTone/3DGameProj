#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"
#include "AsetManager.h"
//キャストが面倒なので
#define GROUP (Group)GameGroup	

//Entityの制御を行うクラスです
class GameController
{
private:
	SoundEngine::SoundSource bgm;
	
	enum class GameGroup : Group
	{
		ALWAYS,	//ゲームの状態に関わらず常に更新と描画を行うグループ
		TITLE,		//タイトル中に更新を行うグループ
		GAME,		//ゲーム中に更新を行うグループ
		PAUSE,		//一時停止中に更新を行うグループ
		END			//ゲーム終了時に更新を行うグループ
	};

	EntityManager entityManager;
	Entity& gameMaster;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& enemy;
	Entity& field;
	Entity& titleController;
	Entity& alwaysCanvas;
	Entity& pauseController;
	Entity& endController;
	Entity& topping;
	const void Title(const GameState& state);
	const void Play(const GameState& state);
	const void Pause(const GameState& state);
	const void End(const GameState& state);
	const void Always();
public:
	GameController();
	~GameController() = default;
	void CollisionEvent();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};