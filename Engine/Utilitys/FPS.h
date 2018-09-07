#pragma once
#include <atlbase.h>
/*! @class FPS
*   @brief ���Ԃ��v�����邽�߂̃N���X�ł�
*/
class FPS
{
private:
	float time;						//���ݎ���
	float deltaTime;				//����
	int frameRate;					//���݂̃t���[���̒l
	float second;					//�b���𑪂�
	float frameCount;				//�t���[���J�E���^
	static constexpr float MaxFps = 60;
	LARGE_INTEGER preCount;			//�����t���l�^ long long
	LARGE_INTEGER frequency;
	LARGE_INTEGER GetCounter() const;
	LARGE_INTEGER GetCountFrequency() const;
public:
	FPS();
	~FPS();
	/*!
	* @brief  ���Ԃ̌v�������܂�
	*/
	void UpDate();
	/*!
	* @brief  �A�v���P�[�V�����N��������̎��Ԃ�Ԃ��܂�
	* @retrun [float] time
	*/
	float GetTime() const;
	/*!
	* @brief  �O�̃t���[���ƍ��̃t���[���̎��ԍ���Ԃ��܂�
	* @retrun [float] deltaTime
	*/
	float GetDeltaTime() const;
	/*!
	* @brief  ���݂̃t���[�����[�g��Ԃ��܂�
	* @retrun [int] frameRate
	*/
	int GetFrameRate() const;

};

