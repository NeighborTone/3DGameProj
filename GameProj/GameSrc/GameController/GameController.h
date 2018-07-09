#pragma once
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
class GameController
{
private:
	EntityManager entityManager;
	Entity& player;
	Entity& ground;
	Entity& shot;

public:
	GameController();
	~GameController();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};