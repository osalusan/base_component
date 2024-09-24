#include "texturecacheManager.h"
#include "renderer.h"

std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> TextureCacheManager::m_Texture;

void TextureCacheManager::LoadTexture(const wchar_t* filename, TexMetadata& meta, ScratchImage& image, ID3D11ShaderResourceView*& texture)
{
	if (m_Texture.count(filename) > 0)
	{
		texture = m_Texture[filename];
		return;
	}
	LoadFromWICFile(filename, WIC_FLAGS_NONE, &meta, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), meta, &texture);
	m_Texture[filename] = texture;
}
