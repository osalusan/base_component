#include "texturecacheManager.h"
#include "renderer.h"

std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> TextureCacheManager::m_Texture;

void TextureCacheManager::LoadTexture(const wchar_t* filename, TexMetadata& meta, ScratchImage& image, ID3D11ShaderResourceView*& texture)
{
	//if (m_Texture.count(filename) > 0)
	//{
	//	texture = m_Texture[filename];
	//	return;
	//}
	LoadFromWICFile(filename, WIC_FLAGS_NONE, &meta, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), meta, &texture);
	m_Texture[filename] = texture;
}

void TextureCacheManager::LoadTexture(const wchar_t* filename, TexMetadata& meta, ScratchImage& image, ScratchImage& mip, ID3D11ShaderResourceView*& texture)
{
	if (m_Texture.count(filename) > 0)
	{
		texture = m_Texture[filename];
		return;
	}
	LoadFromWICFile(filename, WIC_FLAGS_NONE, &meta, image);
	GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mip);
	CreateShaderResourceView(Renderer::GetDevice(), mip.GetImages(), mip.GetImageCount(), mip.GetMetadata(), &texture);
	assert(texture);

	m_Texture[filename] = texture;
}
