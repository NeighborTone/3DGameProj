#pragma once
#include "../ECS/Components/Transform.hpp"
#include "../ECS/Components/GameStateComponent.h"
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
		return Angles(e.GetComponent<T>().angle);
	}
	//大きさ取得
	template<typename T = TransformComponent>
	static Scale GetScale(Entity& e)
	{
		return Scale(e.GetComponent<T>().scale);
	}
	//半径を取得
	template<typename T = TransformComponent>
	static Scale GetRadius(Entity& e)
	{
		return Scale(e.GetComponent<T>().scale / 2);
	}
	//トランスコンポーネントごと取得
	template<typename T = TransformComponent>
	static T GetTransform(Entity& e)
	{
		return e.GetComponent<T>();
	}
	//ゲームの状態を取得
	template<typename T = GameStateComponent, typename TState = GameState>
	static TState GetGameState(Entity& e)
	{
		return e.GetComponent<T>().GetCurrentState();
	}
	//色をグラデーションさせる
	//1,変化させたいもの,2色の変化量
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
