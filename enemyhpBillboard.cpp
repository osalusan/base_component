#include "enemyhpBillboard.h"
#include "enemybase.h"
#include "manager.h"
#include "player_camera.h"

// ---------------------- HPバー ----------------------
void EnemyHelth_Billboard::LoadTexture()
{
	Load(L"asset\\texture\\gage.png"); 
}

void EnemyHelth_Billboard::SetEnemyPointer(EnemyBase* enemy,float hp)
{
	_enemy = enemy;
	SetBillBoard(_enemy->_TransForm->_Position, { 10.0f,0.5f,10.0f });
	_maxhp = hp;
}
void EnemyHelth_Billboard::Update()
{
	BillBoard::Update();
	_TransForm->_Position.x = _enemy->_TransForm->_Position.x;
	_TransForm->_Position.y = _enemy->_TransForm->_Position.y + 7.0f;
	_TransForm->_Position.z = _enemy->_TransForm->_Position.z - _enemy->_TransForm->_Scale.z;
}
void EnemyHelth_Billboard::Draw()
{

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float x = ((_enemy->_hp / _maxhp) * 1.95f);
	float xt = (_enemy->_hp / _maxhp);
	float xp = x + (0.3f *(1.0f - xt));

	xp -= 1.0f;
	if (xp <= -1.0f) { xp = -1.0f; }

	vertex[0].Position = XMFLOAT3(-0.7f, 0.55f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.02f);

	vertex[1].Position = XMFLOAT3(xp, 0.55f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(xt, 0.02f);

	vertex[2].Position = XMFLOAT3(-0.7f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(xp, -1.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(xt, 1.0f);


	Player_Camera* camera = Manager::GetScene()->GetGameObject<Player_Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;
	
	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x + _position.x, _TransForm->_Position.y + _position.y, _TransForm->_Position.z + _position.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(world);
	
	//頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
	
	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	
	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
	
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	
	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
}
// ---------------------- HPフレーム ----------------------
void EnemyHpFrame_Billboard::LoadTexture()
{
	Load(L"asset\\texture\\T_enemyHpFrame_Black.png"); 
	_texTop.y = 0.02f;
}

void EnemyHpFrame_Billboard::SetEnemyPointer(EnemyBase* enemy)
{
	_enemy = enemy;
	SetBillBoard(_enemy->_TransForm->_Position, { 10.0f,0.5f,10.0f });
}

void EnemyHpFrame_Billboard::Update()
{
	BillBoard::Update();
	_TransForm->_Position.x = _enemy->_TransForm->_Position.x;
	_TransForm->_Position.y = _enemy->_TransForm->_Position.y + 7.0f;
	_TransForm->_Position.z = _enemy->_TransForm->_Position.z - _enemy->_TransForm->_Scale.z;
}
// ---------------------- HPバーの背景 ----------------------
void EnemyHpSpace_Billboard::LoadTexture()
{
	Load(L"asset\\texture\\T_enemyHpSpace.png");
	_texTop.y = 0.02f;
}

void EnemyHpSpace_Billboard::SetEnemyPointer(EnemyBase* enemy)
{
	_enemy = enemy;
	SetBillBoard(_enemy->_TransForm->_Position, { 10.0f,0.5f,10.0f });
}

void EnemyHpSpace_Billboard::Update()
{
	BillBoard::Update();
	_TransForm->_Position.x = _enemy->_TransForm->_Position.x;
	_TransForm->_Position.y = _enemy->_TransForm->_Position.y + 7.0f;
	_TransForm->_Position.z = _enemy->_TransForm->_Position.z - _enemy->_TransForm->_Scale.z;
}
