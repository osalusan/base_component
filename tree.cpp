#include "tree.h"
#include "texturecacheManager.h"
void Tree::Uninit()
{
	RemoveComponents();

	m_VertexBuffer->Release();
}
void Tree::Loading()
{
	for (int i = 0; i < 100; i++)
	{
		//テクスチャ読み込み
		TexMetadata metadata;
		ScratchImage image;

		TextureCacheManager::LoadTexture(L"asset\\texture\\Tree04_2K.png", metadata, image, m_Texture);
		assert(m_Texture);
	}
}

void Tree::UnLoad()
{
	m_Texture->Release();
}
