#pragma once
#include "../ESC/Component.hpp"
class GameController
{
private:
	EntityManager entMane;
	Entity& me;
	Entity& cameraMan;
public:
	//���\�[�X�m�ۂ̓R���X�g���N�^�ōs���BAddComponent��
	GameController();
	//����̓f�X�g���N�^
	~GameController();
	void Init();
	void UpDate();
	void Draw3D();
	void Draw2D();
	void Finalize();

};