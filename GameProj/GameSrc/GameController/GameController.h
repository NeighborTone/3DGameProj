#pragma once
#include "../ESC/Component.hpp"
class GameController
{
private:
	EntityManager entityManager;
	Entity& cameraMan;
	Texture  tex;
	Mesh me;
public:
	//リソース確保はコンストラクタで行う。AddComponent等
	GameController();
	//解放はデストラクタ
	~GameController();
	void Init();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};