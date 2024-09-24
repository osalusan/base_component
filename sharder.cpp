#include "component.h"
#include "sharder.h"

void Sharder::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"Shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\unlitTexturePS.cso");
}

void Sharder::Unit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Sharder::Draw()
{
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}
