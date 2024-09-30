#pragma once

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp-vc143-mt.lib")

#include "component.h"


//変形後頂点構造体
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;
	int				BoneNum;
	std::string		BoneName[4];//本来はボーンインデックスで管理するべき
	float			BoneWeight[4];
};

//ボーン構造体
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
	XMMATRIX WorldMatrix;
};

class AnimationModel : public Component
{
private:
	const aiScene* m_AiScene = nullptr;
	std::unordered_map<std::string, const aiScene*> m_Animation;

	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;//変形後頂点データ
	std::unordered_map<std::string, BONE> m_Bone;//ボーンデータ（名前で参照）

public:
	using Component::Component;

	bool _visible = true;
	void Load(const char* FileName);
	void Unit() override;
	void Draw() override;

	void LoadAnimation(const char* FileName, const char* Name);
	void Update(const char* AnimationName1, int Frame1, const char* AnimationName2, int Frame2, float BlendRatio);
	void CreateBone(aiNode* node);
	void Update(const char* AnimationName1, int Frame1);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	XMMATRIX GetBoneMatrix(std::string boneName) {return m_Bone[boneName].WorldMatrix;}

	XMMATRIX AiMatrixToXMMATRIX(const aiMatrix4x4& mat) {
		// AssimpのaiMatrix4x4は行優先、XMMATRIXは列優先なので転置する
		return XMMATRIX(
			mat.a1, mat.a2, mat.a3, mat.a4,
			mat.b1, mat.b2, mat.b3, mat.b4,
			mat.c1, mat.c2, mat.c3, mat.c4,
			mat.d1, mat.d2, mat.d3, mat.d4 
		);
	}
};