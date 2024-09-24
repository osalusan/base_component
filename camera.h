#pragma once
#include "gameobj.h"

class Camera :public GameObject
{
protected:
	XMFLOAT3 _Target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float _length = 20.0f;
	XMFLOAT4X4 _ViewMatrix = {};

public:
	Camera() {}
	Camera(XMFLOAT3 position, XMFLOAT3 rotation);
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	virtual ~Camera() {};
	virtual void SetTarget(XMFLOAT3 position);
	XMMATRIX GetViewMatrix() {
		return XMLoadFloat4x4(&_ViewMatrix);
	};
};