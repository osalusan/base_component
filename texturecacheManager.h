#pragma once
#include "main.h"
#include <string>
#include <unordered_map>
class TextureCacheManager {
private:
	//ID3D11ShaderResourceView* m_Texture = nullptr;
	static std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;
public:
	static void LoadTexture(const wchar_t * filename ,TexMetadata& meta, ScratchImage& image) {

		if (m_Texture.count(filename) > 0)
		{
			m_Texture = m_Texture[filename];
			return;
		}
		LoadFromWICFile(filename, WIC_FLAGS_NONE, &meta, image);
		m_Texture[filename] = m_Texture;
	};
};