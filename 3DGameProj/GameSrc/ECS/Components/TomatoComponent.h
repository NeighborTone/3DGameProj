#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"
#include "../Components/ComponentData/MetaData.hpp"
#include <vector>

//UFO�ɂ�����Ȃ��悤�Ɏ��g�}�g
//�S���������ƃQ�[���I�[�o�[�ɂȂ�܂�
class TomatoComponent : public Component
{
private:
	static constexpr float FieldOut = 490;
	static constexpr float OnGround = 4;
	Mesh mesh;
	Texture tex;
	std::vector<ToppingData> data;
	void Executioners();
public:
	TomatoComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB

	void GameOver(GameState& state) const;
	//�f�[�^�擾
	[[nodiscard]] const std::vector<ToppingData>& GetData() const;
	//�����Ă���Ƃ��̓���
	void ToBeKidnapped(Entity& enemy);
};
