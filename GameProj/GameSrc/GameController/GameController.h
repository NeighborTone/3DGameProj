#pragma once
#include"../ECS/ECS.hpp"

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
	void Init();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};