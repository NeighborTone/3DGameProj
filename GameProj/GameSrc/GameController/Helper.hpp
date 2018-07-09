#pragma once
#include "../ECS/Components/Transform.hpp"

//冗長になりがちなのでよく使うコンポーネントの取得関数を用意しておく
class ComAssist
{
public:
	//ポジション取得
	template<typename T = TransformComponent>
	static Pos GetPos(Entity& e)
	{
		return Pos(e.GetComponent<T>().pos);
	}
	//アングル取得
	template<typename T = TransformComponent>
	static Angles GetAngles(Entity& e)
	{
		return Angles(e.GetComponent<T>().angles);
	}
	//トランスコンポーネントごと取得
	template<typename T = TransformComponent>
	static T GetTransform(Entity& e)
	{
		return e.GetComponent<T>();
	}

};

