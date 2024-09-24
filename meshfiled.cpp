#include "meshfiled.h"


float g_FiledHeight[FILED_MAX][FILED_MAX] =
{
	{15.0f, 13.5f, 12.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 11.5f, 12.0f, 9.5f, 11.0f, 13.5f, 13.0f, 12.5f, 13.0f, 13.5f, 10.0f, 9.5f, 9.0f, 5.5f, 7.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f},
	{13.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 16.5f, 6.0f, 13.5f, 9.0f, 10.5f, 8.0f, 10.5f, 3.0f, 2.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f},
	{9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 12.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f},
	{8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 10.5f, 10.0f, 8.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f},
	{8.0f, 7.5f, 7.0f, 6.5f, 10.0f, 10.5f, 9.0f, 8.5f, 8.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f},
	{7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f},
	{7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f},
	{6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f},
	{6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f},
	{5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f},
	{5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f},
	{4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f},
	{4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f},
	{3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f},
	{3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f},
	{3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f},
	{4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f},
	{4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 12.5f},
	{5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f},
	{5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f},
	{6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 6.5f},
	{6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.0f},
	{7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 7.5f},
	{7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.0f},
	{8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 8.5f},
	{8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.0f},
	{9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 9.5f},
	{9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f, 10.0f},
	{10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f,10.0f,10.0f,10.0f},
	{10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f,10.0f,10.0f,10.0f},
	{10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.0f, 5.5f, 5.0f, 4.5f, 4.0f, 3.5f, 3.0f, 4.0f, 4.5f, 5.0f, 5.5f, 6.0f, 6.5f, 7.0f, 7.5f, 8.0f, 8.5f, 9.0f, 9.5f, 10.0f,10.0f,10.0f,10.0f},

};

void MeshFiled::Init()
{
	Load(L"asset\\texture\\rocky_terrain_02_diff_2k.png");
	//Load(L"asset\\texture\\oruga_T001.png");
	InitComponent();
	// Vertexバッファ生成
	{
		for (int x = 0; x < FILED_MAX; x++)
		{
			for (int z = 0; z < FILED_MAX; z++)
			{
				XMFLOAT3 vx,vz,vn;
				m_Vertex[x][z].Position = XMFLOAT3(
					(x - 10) * 5.0f,
					g_FiledHeight[x][z],
					(z - 10) * -5.0f);
				m_Vertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
				m_Vertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = XMFLOAT2(x * 0.5f, z * 0.5f);
			}
		}
		// 法線ベクトルの算出
		for (int x = 1; x <= FILED_MAX -2; x++)
		{
			for (int z = 1; z <= FILED_MAX -2; z++)
			{
				XMFLOAT3 vx, vz, vn;
				vx.x = m_Vertex[x + 1][z].Position.x - m_Vertex[x - 1][z].Position.x;
				vx.y = m_Vertex[x + 1][z].Position.y - m_Vertex[x - 1][z].Position.y;
				vx.z = m_Vertex[x + 1][z].Position.z - m_Vertex[x - 1][z].Position.z;

				vz.x = m_Vertex[x][z - 1].Position.x - m_Vertex[x][z + 1].Position.x;
				vz.y = m_Vertex[x][z - 1].Position.y - m_Vertex[x][z + 1].Position.y;
				vz.z = m_Vertex[x][z - 1].Position.z - m_Vertex[x][z + 1].Position.z;
				
				// 外積
				vn.x = vz.y * vx.z - vz.z * vx.y;
				vn.y = vz.z * vx.x - vz.x * vx.z;
				vn.z = vz.x * vx.y - vz.y * vx.x;

				// 正規化
				float len = sqrtf(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
				vn.x /= len;
				vn.y /= len;
				vn.z /= len;
				
				m_Vertex[x][z].Normal = vn;
			}
		}

		//頂点バッファの生成
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * FILED_MAX * FILED_MAX;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	// Indexバッファ生成
	{
		unsigned int index[((FILED_MAX + 1) * 2) * (FILED_MAX -1) - 1];
		int i = 0;
		for (int x = 0; x < FILED_MAX - 1; x++)
		{
			for (int z = 0; z < FILED_MAX; z++)
			{
				index[i] = x * FILED_MAX + z;
				i++;

				index[i] = (x + 1) * FILED_MAX + z;
				i++;
			}
			if (x == FILED_MAX - 2)
				break;

			// 縮退頂点用
			index[i] = (x + 1) * FILED_MAX + (FILED_MAX -1 );
			i++;

			index[i] = (x + 1) * FILED_MAX;
			i++;
		}

		//インデックスバッファの生成
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((FILED_MAX + 1) * 2) * (FILED_MAX - 1));
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

}

void MeshFiled::Uninit()
{
	RemoveComponent();
	m_VertexBuffer->Release();
	m_Texture->Release();

}

void MeshFiled::Update()
{
	UpdateComponent();
}

void MeshFiled::Draw()
{
	DrawComponent();

	//ワールドマトリクス設定
	XMMATRIX world, scl, rot, trans;
	scl = XMMatrixScaling(_TransForm->_Scale.x, _TransForm->_Scale.y, _TransForm->_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(_TransForm->_Rotation.x, _TransForm->_Rotation.y, _TransForm->_Rotation.z);
	trans = XMMatrixTranslation(_TransForm->_Position.x, _TransForm->_Position.y, _TransForm->_Position.z);
	world = scl * rot * trans;
	Renderer::SetWorldMatrix(world);

	//頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer,DXGI_FORMAT_R32_UINT,0);


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
	//Renderer::GetDeviceContext()->Draw(21 * 21, 0);
	Renderer::GetDeviceContext()->DrawIndexed((FILED_MAX * 2) * FILED_MAX - 2, 0, 0);
	

}

void MeshFiled::InitComponent()
{
	_sharder = new Sharder(this);_sharder->Init();
}

void MeshFiled::UpdateComponent()
{
	_sharder->Update();
}

void MeshFiled::DrawComponent()
{
	_sharder->Draw();
}

void MeshFiled::RemoveComponent()
{
	_sharder->Unit(); delete _sharder;
}

float MeshFiled::GetHeight(XMFLOAT3 position)
{
	int x, z;
	// ブロック番号算出
	x = position.x / 5.0f + 10.0f;
	z = position.z / -5.0f + 10.0f;

	XMFLOAT3 pos0, pos1, pos2, pos3;
	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	XMFLOAT3 v12, v1p;
	v12.x = pos2.x - pos1.x;
	v12.y = pos2.y - pos1.y;
	v12.z = pos2.z - pos1.z;

	v1p.x = position.x - pos1.x;
	v1p.y = position.y - pos1.y;
	v1p.z = position.z - pos1.z;

	// 外積
	float cy = v12.z * v1p.x - v12.x * v1p.z;

	float py;
	XMFLOAT3 n;
	if (cy > 0.0f)
	{
		// 左上ポリゴン
		XMFLOAT3 v10;
		v10.x = pos0.x - pos1.x;
		v10.y = pos0.y - pos1.y;
		v10.z = pos0.z - pos1.z;

		// 外積
		n.x = v10.y * v12.z - v10.z * v12.y;
		n.y = v10.z * v12.x - v10.x * v12.z;
		n.z = v10.x * v12.y - v10.y * v12.x;
	}
	else
	{
		// 右下ポリゴン
		XMFLOAT3 v13;
		v13.x = pos3.x - pos1.x;
		v13.y = pos3.y - pos1.y;
		v13.z = pos3.z - pos1.z;

		// 外積
		n.x = v12.y * v13.z - v12.z * v13.y;
		n.y = v12.z * v13.x - v12.x * v13.z;
		n.z = v12.x * v13.y - v12.y * v13.x;
	}

	// 高さ取得
	py = -((position.x - pos1.x) * n.x + (position.z - pos1.z) * n.z) / n.y + pos1.y;
	return py;
}
void MeshFiled::Load(const wchar_t* FileName)
{
	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(FileName, WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);
}