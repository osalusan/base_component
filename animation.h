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
	//フレーム単位
	int m_Count = 0;						//時間のカウント
	float _maxTime = 60.0f;				//最大時間
	float _minValue = -1.0f;			//最小数値
	float _maxValue = 1.0f;				//最大数値
	float _value = 0.0f;				//１フレームで変化する値
	float _easingTime = 0.0f;			//０～１の数値
	float _easingValue = 0.0f;			//easing関数のリターん値を格納する
	bool _reverse = false;				//m_Countが0とmaxTimeになった時に_directionが反転する
	bool _animationFlag = true;			//アニメーションするかしないか
	bool _animationRecord = false;		//前フレームでアニメーションをしているかどうか
	float _loop = true;					//ループするかの設定
	std::list<XMFLOAT2> _key = {};		//左：時間　右：数値
	EASING _easing = Easing_None;
	DIRECTION _direction = Forward;

	using Component::Component;

	void Init()override {};
	void Unit()override {};
	void Update()override ;
	void Draw()override {};
	//最大時間、最大数値
	void SetFloatData(float maxT, float maxV, float minV) {
		 _maxTime = maxT; _maxValue = maxV; _minValue = minV;
		 _value = (_maxValue - _minValue) / _maxTime;
	};
	float EasingAnimationValue(float value);
	float AnimationFloat();
	void AnimationStart() { _animationFlag = true; };
	void AnimationStop() { _animationFlag = false; };
};