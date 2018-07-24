#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"

//Entity�̐�����s���N���X�ł�
class GameController
{
private:
	enum class GameState
	{
		PLAY,		//�Q�[����
		STOP,		//��~��
	};
	enum GameGroup : std::size_t
	{
		ALWAYS,		//�Q�[���̏�ԂɊւ�炸��ɍX�V�ƕ`����s���O���[�v
		GAME,		//�Q�[�����ɍX�V�ƕ`����s���O���[�v
		END			//����
	};

	void StateMachine();
	void GameStart();
	void GameStop();
	GameState gameState;
	EntityManager entityManager;

	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& enemy;
	Entity& field;
	Entity& map;
	Entity& topping;
	std::vector<Entity*> gameScene;
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