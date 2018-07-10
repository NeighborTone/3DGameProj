#pragma once
#include "../ECS/Components/Transform.hpp"

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
		return Angles(e.GetComponent<T>().angles);
	}
	//�g�����X�R���|�[�l���g���Ǝ擾
	template<typename T = TransformComponent>
	static T GetTransform(Entity& e)
	{
		return e.GetComponent<T>();
	}

};

