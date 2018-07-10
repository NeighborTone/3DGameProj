#pragma once
#include"../ECS/ECS.hpp"
#include "Helper.hpp"
#include "../ECS/Components/ComponentData/Sphere.hpp"
#include "../ECS/Components/ComponentData/Collision.h"
class GameController
{
private:
	EntityManager entityManager;
	Entity& player;
	Entity& shot;
	Entity& skyBox;
	Entity& hoge;
public:
	GameController();
	~GameController();
	void Initialize();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};