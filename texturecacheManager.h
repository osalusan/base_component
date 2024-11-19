#pragma once
#include "main.h"
#include <string>
#include <unordered_map>
class TextureCacheManager {
private:
	//ID3D11ShaderResourceView* m_Texture = nullptr;
	static std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> m_Texture;
public:

	static void LoadTexture(const wchar_t* filename, TexMetadata& meta, ScratchImage& image, ID3D11ShaderResourceView*& texture);
	static void LoadTexture(const wchar_t* filename, TexMetadata& meta, ScratchImage& image, ScratchImage& mip, ID3D11ShaderResourceView*& texture);
};