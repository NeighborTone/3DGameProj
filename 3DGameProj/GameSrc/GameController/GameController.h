#pragma once
#include "../../Engine/Graphics/Particle.h"
#include "../../Engine/Sounds/SoundSource.h"
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"
#include "AsetManager.h"
//�L���X�g���ʓ|�Ȃ̂�
#define GROUP (Group)GameGroup	

//Entity�̐�����s���N���X�ł�
class GameController
{
private:
	SoundEngine::SoundSource bgm;
	
	enum class GameGroup : Group
	{
		ALWAYS,	//�Q�[���̏�ԂɊւ�炸��ɍX�V�ƕ`����s���O���[�v
		TITLE,		//�^�C�g�����ɍX�V���s���O���[�v
		GAME,		//�Q�[�����ɍX�V���s���O���[�v
		PAUSE,		//�ꎞ��~���ɍX�V���s���O���[�v
		END			//�Q�[���I�����ɍX�V���s���O���[�v
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