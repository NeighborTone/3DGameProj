#pragma once
#include "../ECS/Components/Transform.hpp"
#include "../ECS/Components/GameStateComponent.h"
//�璷�ɂȂ肪���Ȃ̂ł悭�g���R���|�[�l���g�̎擾�֐���p�ӂ��Ă���
class ComAssist
{
public:
	//�|�W�V�����擾
	template<typename T = TransformComponent>
	static Pos GetPos(Entity& e)
	{
		return Pos(e.GetComponent<T>().pos);
	}
	//�A���O���擾
	template<typename T = TransformComponent>
	static Angles GetAngles(Entity& e)
	{
		return Angles(e.GetComponent<T>().angle);
	}
	//�傫���擾
	template<typename T = TransformComponent>
	static Scale GetScale(Entity& e)
	{
		return Scale(e.GetComponent<T>().scale);
	}
	//���a���擾
	template<typename T = TransformComponent>
	static Scale GetRadius(Entity& e)
	{
		return Scale(e.GetComponent<T>().scale / 2);
	}
	//�g�����X�R���|�[�l���g���Ǝ擾
	template<typename T = TransformComponent>
	static T GetTransform(Entity& e)
	{
		return e.GetComponent<T>();
	}
	//�Q�[���̏�Ԃ��擾
	template<typename T = GameStateComponent, typename TState = GameState>
	static TState GetGameState(Entity& e)
	{
		return e.GetComponent<T>().GetCurrentState();
	}
	//�F���O���f�[�V����������
	//1,�ω�������������,2�F�̕ω���
	static void GradationColor(Float4& color, Float4& colorDelta)
	{
		color.r += colorDelta.r;
		color.g += colorDelta.g;
		color.b += colorDelta.b;
		if (color.r <= 0.2f || color.r >= 0.99f) colorDelta.r *= -1;
		if (color.b <= 0.2f || color.b >= 0.99f) colorDelta.b *= -1;
		if (color.g <= 0.2f || color.g >= 0.99f) colorDelta.g *= -1;
	}
};
