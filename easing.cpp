#include "easing.h"
//----------------------------------------------
//参考サイト
//https://easings.net/ja
//----------------------------------------------

//-----------------------
// easeInSine
//-----------------------
float easeInSine(float x)
{
	return 1 - cos((x * XM_PI) / 2);
}

//-----------------------
// easeOutSine
//-----------------------
float easeOutSine(float x)
{
	return sin((x * XM_PI) / 2);
}

//-----------------------
// easeInOutSine
//-----------------------
float easeInOutSine(float x)
{
	return -(cos(XM_PI * x) - 1) / 2;
}

//-----------------------
// easeInQuad
//-----------------------
float easeInQuad(float x)
{
	return x * x;
}

//-----------------------
// easeOutQuad
//-----------------------
float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

//-----------------------
// easeInOutQuad
//-----------------------
float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

//-----------------------
// easeInCubic
//-----------------------
float easeInCubic(float x)
{
	return x * x * x;
}

//-----------------------
// easeOutCubic
//-----------------------
float easeOutCubic(float x)
{
	return 1 - pow(1 - x, 3);
}

//-----------------------
// easeInOutCubic
//-----------------------
float easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}

//-----------------------
// easeInQuart
//-----------------------
float easeInQuart(float x)
{
	return x * x * x * x;
}

//-----------------------
// easeOutQuart
//-----------------------
float easeOutQuart(float x)
{
	return 1 - pow(1 - x, 4);
}

//-----------------------
// easeInOutQuint
//-----------------------
float easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

//-----------------------
// easeInExpo
//-----------------------
float easeInExpo(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

//-----------------------
// easeOutExpo
//-----------------------
float easeOutExpo(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
}

//-----------------------
// easeInOutExpo
//-----------------------
float easeInOutExpo(float x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5 ? pow(2, 20 * x - 10) / 2
		: (2 - pow(2, -20 * x + 10)) / 2;
}

//-----------------------
// easeInCirc
//-----------------------
float easeInCirc(float x)
{
	return 1 - sqrt(1 - pow(x, 2));
}

//-----------------------
// easeOutCirc
//-----------------------
float easeOutCirc(float x)
{
	return sqrt(1 - pow(x - 1, 2));
}

//-----------------------
// easeInOutCirc
//-----------------------
float easeInOutCirc(float x)
{
	return x < 0.5
		? (1 - sqrt(1 - pow(2 * x, 2))) / 2
		: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}

//-----------------------
// easeInBack
//-----------------------
static const float c1 = 1.70158;
static const float c3 = c1 + 1;

float easeInBack(float x)
{
	return c3 * x * x * x - c1 * x * x;
}

//-----------------------
// easeOutBack
//-----------------------
//static const float c1 = 1.70158;
//static const float c3 = c1 + 1;

float easeOutBack(float x)
{
	return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

//-----------------------
// easeInOutBack
//-----------------------
//static const float c1 = 1.70158;
static const float c2 = c1 * 1.525;

float easeInOutBack(float x)
{
	return x < 0.5
		? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
		: (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
}

//-----------------------
// easeInElastic
//-----------------------
static const float c4 = (2 * XM_PI) / 3;

float easeInElastic(float x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
}

//-----------------------
// easeOutElastic
//-----------------------
float easeOutElastic(float x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}

//-----------------------
// easeInOutElastic
//-----------------------
static const float c5 = (2 * XM_PI) / 4.5;

float easeInOutElastic(float x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5
		? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
		: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
}

//-----------------------
// easeInBounce
//-----------------------
float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

//-----------------------
// easeOutBounce
//-----------------------
static const float n1 = 7.5625;
static const float d1 = 2.75;

float easeOutBounce(float x)
{
	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}


//-----------------------
// easeInOutBounce
//-----------------------
float easeInOutBounce(float x)
{
	return x < 0.5
		? (1 - easeOutBounce(1 - 2 * x)) / 2
		: (1 + easeOutBounce(2 * x - 1)) / 2;
}