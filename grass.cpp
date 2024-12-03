#include "grass.h"
#include "player_camera.h"
#include "manager.h"

constexpr int MAX_GRASS = 1000000;
void Grass::Init()
{
	m_Pivot = 1;
	BillBoard::Init();
	m_TransForm->m_Scale = { 2.0f,2.0f,2.0f };

	//ストラクチャバッファ
	{
		XMFLOAT3* pos = new XMFLOAT3[MAX_GRASS];

		int i = 0;
		for (int x = 0; x < 1000; x++) {
			for (int z = 0; z < 1000; z++) {
				pos[i] = XMFLOAT3(x, 0.0f, z);
				i++;
			}
		}

		//ストラクチャードバッファ作成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(XMFLOAT3) * MAX_GRASS;
		bd.StructureByteStride = sizeof(XMFLOAT3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pos;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_PositionBuffer);

		delete[] pos;

		//シェーダーリソースビュー
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = MAX_GRASS;
		Renderer::GetDevice()->CreateShaderResourceView(m_PositionBuffer,
			&srvd, &m_PositionSRV);

	}


}
void Grass::Uninit()
{
	BillBoard::Uninit();
	m_PositionBuffer->Release();
	m_PositionSRV->Release();
}
void Grass::Draw()
{
	DrawComponents();

	if (m_Sprite.x != 0)
	{
		//テクスチャ座標算出(剰余斬)
		float x = m_Animecount % m_Sprite.x * (1.0f / m_Sprite.x);
		float y = m_Animecount / m_Sprite.x * (1.0f / m_Sprite.y);

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = XMFLOAT2(x, y);

		vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = XMFLOAT2(x + 0.25f, y);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(-1.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = XMFLOAT2(x, y + (1.0f / m_Sprite.y));

		vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = XMFLOAT2(x + (1.0f / m_Sprite.x), y + (1.0f / m_Sprite.y));

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	//ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_TransForm->m_Scale.x, m_TransForm->m_Scale.y, m_TransForm->m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_TransForm->m_Rotation.x, m_TransForm->m_Rotation.y, m_TransForm->m_Rotation.z);
	trans = XMMatrixTranslation(m_TransForm->m_Position.x + m_Position.x, m_TransForm->m_Position.y + m_Position.y, m_TransForm->m_Position.z + m_Position.z);
	world = scale * rot * trans;
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

	// ストラクチャードバッファ設定
	Renderer::GetDeviceContext()->VSSetShaderResources(
		2, 1, & m_PositionSRV);
	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// アルファトゥカバレッジ有効
	Renderer::SetATCEnable(true);

	//ポリゴン描画
	//Renderer::GetDeviceContext()->Draw(4, 0);
	Renderer::GetDeviceContext()->DrawInstanced(4, MAX_GRASS,0,0);

	Renderer::SetATCEnable(false);

}
