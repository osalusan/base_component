#pragma once
#include "main.h"
class TextureCacheManager {
private:
	ID3D11ShaderResourceView* m_Texture = nullptr;
public:
	static void LoadTexture(const wchar_t * filename ,TexMetadata& meta, ScratchImage& image) {
		LoadFromWICFile(filename, WIC_FLAGS_NONE, &meta, image);
	};
};