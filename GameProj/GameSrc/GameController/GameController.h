#pragma once
#include "../ECS/Component.hpp"

class GameController
{
private:
	EntityManager entityManager;
	Entity& Player;
	Entity& ground;

public:
	GameController();
	~GameController();
	void Init();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};