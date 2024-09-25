#include "player_state.h"
#include "player.h"
#include "manager.h"
// --------------------------- プレイヤーの体力 ---------------------------
void Player_Hp::Init()
{
	Polygon2D::Init();
	_player = Manager::GetScene()->GetPlayerCharcter();

	m_TransForm->_Position = { SCREEN_WIDTH * 0.02f,SCREEN_HEIGHT * 0.02f,0.0f };
	m_TransForm->_Scale = {SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.03f,0.0f};
	_maxhp = _player->m_Hp;
}

void Player_Hp::Update()
{
	Polygon2D::Update();
}

void Player_Hp::Draw()
{
	float x = _player->m_Hp / _maxhp;
	float xrp = (SCREEN_WIDTH * 0.5f) * x +SCREEN_WIDTH * 0.02f;
	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = XMFLOAT3(m_TransForm->_Position.x, m_TransForm->_Position.y, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(xrp, m_TransForm->_Position.y, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(x, 0.0f);

	vertex[2].Position = XMFLOAT3(m_TransForm->_Position.x, m_TransForm->_Position.y + m_TransForm->_Scale.y, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(xrp, m_TransForm->_Position.y + m_TransForm->_Scale.y, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(x, 1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	Polygon2D::Draw();

}

void Player_Hp::LoadTexture()
{
	Load(L"asset\\texture\\T_HP.png");
}

// --------------------------- プレイヤーの体力フレーム ---------------------------
void Player_HpFrame::Init()
{
	//Polygon2D::Init();

	//m_TransForm->_Position = { SCREEN_WIDTH * 0.05f,SCREEN_HEIGHT * 0.5f,0.0f };
	//m_TransForm->_Scale = { SCREEN_WIDTH * 0.8f,SCREEN_HEIGHT * 0.15f,0.0f };
}

void Player_HpFrame::LoadTexture()
{
	//Load(L"asset\\texture\\T_HPFrame.png");
}
// --------------------------- プレイヤーのスタミナ ---------------------------
void Player_Stamina::Init()
{
	Polygon2D::Init();
	_player = Manager::GetScene()->GetPlayerCharcter();

	m_TransForm->_Position = { SCREEN_WIDTH * 0.02f,SCREEN_HEIGHT * 0.06f,0.0f };
	m_TransForm->_Scale = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.03f,0.0f };
	_maxstamina = _player->m_Stamina;
}

void Player_Stamina::Update()
{
	Polygon2D::Update();
}

void Player_Stamina::Draw()
{
	float x = _player->m_Stamina / _maxstamina;
	float xrp = (SCREEN_WIDTH * 0.5f) * x + SCREEN_WIDTH * 0.02f;
	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = XMFLOAT3(m_TransForm->_Position.x, m_TransForm->_Position.y, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(xrp, m_TransForm->_Position.y, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(x, 0.0f);

	vertex[2].Position = XMFLOAT3(m_TransForm->_Position.x, m_TransForm->_Position.y + m_TransForm->_Scale.y, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(xrp, m_TransForm->_Position.y + m_TransForm->_Scale.y, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(x, 1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	Polygon2D::Draw();
}

void Player_Stamina::LoadTexture()
{
	Load(L"asset\\texture\\T_Stamina.png");
}

