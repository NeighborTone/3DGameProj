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
	enum GameGroup : std::size_t
	{
		ALWAYS,	//�Q�[���̏�ԂɊւ�炸��ɍX�V�ƕ`����s���O���[�v
		TITLE,		//�^�C�g�����ɍX�V���s���O���[�v
		GAME,		//�Q�[�����ɍX�V���s���O���[�v
		PAUSE,		//�ꎞ��~���ɍX�V���s���O���[�v
		END			//����
	};

	EntityManager entityManager;
	Entity& gameMaster;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& enemy;
	Entity& field;
	Entity& titleCanvas;
	Entity& gameCanvas;
	Entity& pauseCanvas;
	Entity& topping;
	const void Title(const GameState state);
	const void Play(const GameState state);
	const void Pause(const GameState state);
	const void Always();
	const void SetParameter();
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