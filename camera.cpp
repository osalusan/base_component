#include "camera.h"

Camera::Camera(XMFLOAT3 position, XMFLOAT3 rotation )
{
	_TransForm->_Position = position;
	_TransForm->_Rotation = rotation;
}

void Camera::Init()
{
	InitComponent();
}

void Camera::Uninit()
{
	RemoveComponent();
}

void Camera::Update()
{
	UpdateComponent();
}

void Camera::Draw()
{

	XMFLOAT3 up = { 0.0f,1.0f,0.0f };
	XMFLOAT3 position = _TransForm->_Position;

	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&_Target), XMLoadFloat3(&up));

	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&_ViewMatrix, viewMatrix);

	//プロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projectionMatrix);

	DrawComponent();
}

void Camera::InitComponent()
{

}

void Camera::UpdateComponent()
{

}

void Camera::DrawComponent()
{

}

void Camera::RemoveComponent()
{

}

void Camera::SetTarget(XMFLOAT3 position)
{
	_Target = position;
}

