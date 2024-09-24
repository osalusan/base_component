#include "animation.h"
#include "easing.h"


void Animation::Update()
{
	if (!_animationRecord) {
		_count = 0; 
		_reverse =false;
	}
	else
	{	
		if (_loop)
		{
			if (_maxTime <= _count) {
				_count = 0;
				if (_reverse) { _direction = Back; _count = _maxTime; }//アニメーションの反転
			}
			if (0 > _count) {
				if (_reverse) { _direction = Forward; }//アニメーションの反転
				_count = 0;
			}
		}
		if (_direction == Forward) { _count++; }
		if (_direction == Back) { _count--; }

		_value = (_maxValue - _minValue) / _maxTime;
	}

	_animationRecord = false;
}

float Animation::EasingAnimationValue(float value)
{
	
	_easingTime = _count / _maxTime;

	_easingValue = _easingTime;

	switch (_easing)
	{
	case InSine:
		_easingValue = easeInSine(_easingTime);
		break;
	case OutSine:
		_easingValue = easeOutSine(_easingTime);
		break;
	case InOutSine:
		_easingValue = easeInOutSine(_easingTime);
		break;
	case InQuad:
		_easingValue = easeInQuad(_easingTime);
		break;
	case OutQuad:
		_easingValue = easeOutQuad(_easingTime);
		break;
	case InOutQuad:
		_easingValue = easeInOutQuad(_easingTime);
		break;
	case InCubic:
		_easingValue = easeInCubic(_easingTime);
		break;
	case OutCubic:
		_easingValue = easeOutCubic(_easingTime);
		break;
	case InOutCubic:
		_easingValue = easeInOutCubic(_easingTime);
		break;
	case InQuart:
		_easingValue = easeInQuart(_easingTime);
		break;
	case OutQuart:
		_easingValue = easeOutQuart(_easingTime);
		break;
	case InOutQuint:
		_easingValue = easeInOutQuint(_easingTime);
		break;
	case InExpo:
		_easingValue = easeInExpo(_easingTime);
		break;
	case OutExpo:
		_easingValue = easeOutExpo(_easingTime);
		break;
	case InOutExpo:
		_easingValue = easeInOutExpo(_easingTime);
		break;
	case InCirc:
		_easingValue = easeInCirc(_easingTime);
		break;
	case OutCirc:
		_easingValue = easeOutCirc(_easingTime);
		break;
	case InOutCirc:
		_easingValue = easeInOutCirc(_easingTime);
		break;
	case InBack:
		_easingValue = easeInBack(_easingTime);
		break;
	case OutBack:
		_easingValue = easeOutBack(_easingTime);
		break;
	case InOutBack:
		_easingValue = easeInOutBack(_easingTime);
		break;
	case InElastic:
		_easingValue = easeInElastic(_easingTime);
		break;
	case OutElastic:
		_easingValue = easeOutElastic(_easingTime);
		break;
	case InOutElastic:
		_easingValue = easeInOutElastic(_easingTime);
		break;
	case InBounce:
		_easingValue = easeInBounce(_easingTime);
		break;
	case OutBounce:
		_easingValue = easeOutBounce(_easingTime);
		break;
	case InOutBounce:
		_easingValue = easeInOutBounce(_easingTime);
		break;
	default:
		break;
	}

	if (_easing == Easing_None) { return value; }
	return _easingValue * value;
}

float Animation::AnimationFloat()
{

	_animationRecord = true;

	float valueT = _minValue + (_value * _count);

	if (_count >= _maxTime) { return 0; }
	return EasingAnimationValue(valueT);
	
}
