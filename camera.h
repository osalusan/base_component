#pragma once
#include "gameobj.h"

class Camera :public GameObject
{
protected:
	XMFLOAT3 _Target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float _length = 20.0f;
	XMFLOAT4X4 _ViewMatrix = {};

	const float _LENGTH_MIN = 10.0f;
	const float _LENGTH_MAX = 25.0f;
public:
	Camera() {}
	Camera(XMFLOAT3 position, XMFLOAT3 rotation);
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	virtual ~Camera() {};
	virtual void SetTarget(XMFLOAT3 position);
	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&_ViewMatrix);
	};
};