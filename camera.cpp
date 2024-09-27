#include "camera.h"

Camera::Camera(XMFLOAT3 position, XMFLOAT3 rotation )
{
	m_TransForm->m_Position = position;
	m_TransForm->m_Rotation = rotation;
}

void Camera::Init()
{
	InitComponents();
}

void Camera::Uninit()
{
	RemoveComponents();
}

void Camera::Update()
{
	UpdateComponents();
}

void Camera::Draw()
{

	XMFLOAT3 up = { 0.0f,1.0f,0.0f };
	XMFLOAT3 position = m_TransForm->m_Position;

	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&_Target), XMLoadFloat3(&up));

	Renderer::SetViewMatrix(viewMatrix);

	XMStoreFloat4x4(&_ViewMatrix, viewMatrix);

	//プロジェクションマトリクス設定
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(projectionMatrix);

	DrawComponents();
}

void Camera::InitComponents()
{

}

void Camera::UpdateComponents()
{

}

void Camera::DrawComponents()
{

}

void Camera::RemoveComponents()
{

}

void Camera::SetTarget(XMFLOAT3 position)
{
	_Target = position;
}

