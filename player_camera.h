#pragma once
#include "camera.h"
class Player_Camera :public Camera
{
private:
	XMFLOAT2 _MousePos = {};
	XMFLOAT2 _OldMousePos = {};
	class Player* _Player = {};
	int m_Count = 0;
public:
	using Camera::Camera;
	void Init()override;
	void Update()override;
};