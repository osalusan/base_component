#pragma once
#include "component.h"
#include <list>
typedef enum
{
	Forward = 0,
	Back

}DIRECTION;

typedef enum
{
	Easing_None = 0,
	InSine ,
	OutSine,
	InOutSine,
	InQuad,
	OutQuad,
	InOutQuad,
	InCubic,
	OutCubic,
	InOutCubic,
	InQuart,
	OutQuart,
	InOutQuint,
	InExpo,
	OutExpo,
	InOutExpo,
	InCirc,
	OutCirc,
	InOutCirc,
	InBack,
	OutBack,
	InOutBack,
	InElastic,
	OutElastic,
	InOutElastic,
	InBounce,
	OutBounce,
	InOutBounce

}EASING;

class Animation :public Component
{

public:
	//�t���[���P��
	int m_Count = 0;						//���Ԃ̃J�E���g
	float _maxTime = 60.0f;				//�ő厞��
	float _minValue = -1.0f;			//�ŏ����l
	float _maxValue = 1.0f;				//�ő吔�l
	float _value = 0.0f;				//�P�t���[���ŕω�����l
	float _easingTime = 0.0f;			//�O�`�P�̐��l
	float _easingValue = 0.0f;			//easing�֐��̃��^�[��l���i�[����
	bool _reverse = false;				//m_Count��0��maxTime�ɂȂ�������_direction�����]����
	bool _animationFlag = true;			//�A�j���[�V�������邩���Ȃ���
	bool _animationRecord = false;		//�O�t���[���ŃA�j���[�V���������Ă��邩�ǂ���
	float _loop = true;					//���[�v���邩�̐ݒ�
	std::list<XMFLOAT2> _key = {};		//���F���ԁ@�E�F���l
	EASING _easing = Easing_None;
	DIRECTION _direction = Forward;

	using Component::Component;

	void Init()override {};
	void Unit()override {};
	void Update()override ;
	void Draw()override {};
	//�ő厞�ԁA�ő吔�l
	void SetFloatData(float maxT, float maxV, float minV) {
		 _maxTime = maxT; _maxValue = maxV; _minValue = minV;
		 _value = (_maxValue - _minValue) / _maxTime;
	};
	float EasingAnimationValue(float value);
	float AnimationFloat();
	void AnimationStart() { _animationFlag = true; };
	void AnimationStop() { _animationFlag = false; };
};