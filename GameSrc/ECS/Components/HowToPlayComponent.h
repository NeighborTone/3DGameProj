#pragma once
#include "../ECS.hpp"
#include "../../Engine.h"
#include "../../Utilitys/Easing.hpp"
#include "ComponentData/MetaData.hpp"

class HowToPlayComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 30;
	//�L�[�ړ������p
	Text moveText;
	//�V���b�g�����p
	Text shotText;
	//HowToPlay�̏o�����̐����p
	Text howToText;
	UIData howToData;
	UIData moveData;
	UIData shotData;
	//�B���Ă��邩
	bool isHide;
	//�e�L�X�g���o�Ă��邩
	bool isShow;
	//�������߂�p
	Easing drawIn;
public:
	HowToPlayComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	void Reduction(Easing& reduction);
};