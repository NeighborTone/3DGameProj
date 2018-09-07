#pragma once
#include <atlbase.h>
/*! @class FPS
*   @brief 時間を計測するためのクラスです
*/
class FPS
{
private:
	float time;						//現在時刻
	float deltaTime;				//差分
	int frameRate;					//現在のフレームの値
	float second;					//秒数を測る
	float frameCount;				//フレームカウンタ
	static constexpr float MaxFps = 60;
	LARGE_INTEGER preCount;			//符号付数値型 long long
	LARGE_INTEGER frequency;
	LARGE_INTEGER GetCounter() const;
	LARGE_INTEGER GetCountFrequency() const;
public:
	FPS();
	~FPS();
	/*!
	* @brief  時間の計測をします
	*/
	void UpDate();
	/*!
	* @brief  アプリケーション起動時からの時間を返します
	* @retrun [float] time
	*/
	float GetTime() const;
	/*!
	* @brief  前のフレームと今のフレームの時間差を返します
	* @retrun [float] deltaTime
	*/
	float GetDeltaTime() const;
	/*!
	* @brief  現在のフレームレートを返します
	* @retrun [int] frameRate
	*/
	int GetFrameRate() const;

};

