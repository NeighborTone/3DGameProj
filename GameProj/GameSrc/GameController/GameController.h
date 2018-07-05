#pragma once
#include "../ESC/Component.hpp"
class GameController
{
private:
	EntityManager entMane;
	Entity& me;
	Entity& cameraMan;
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