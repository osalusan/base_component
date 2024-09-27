#include "component.h"
#include "sharder.h"

void Sharder::Init()
{
	if (m_Usesharder == 0)
	{
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
			"Shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"Shader\\unlitTexturePS.cso");
	}
	else if (m_Usesharder == 1)
	{
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
			"Shader\\BumpTangentVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"Shader\\BumpTangentPS.cso");
	}
	else if (m_Usesharder == 2)
	{
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
			"Shader\\DisneyPBRVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"Shader\\DisneyPBRPS.cso");
	}
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
