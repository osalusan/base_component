#pragma once
#include "gameobj.h"
#include "sharder.h"
class ParticleEmiter : public GameObject
{
protected:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	Sharder* m_Sharder = {};

	struct PARTICLE {
		bool Enable;
		float lifetime;
		float age;
		XMFLOAT4 color;
		XMFLOAT3 position;
		XMFLOAT3 velocity;
		XMFLOAT3 scale;
		XMFLOAT3 maxscale;
		XMFLOAT3 upscale;
		XMFLOAT3 num;
	};

	static const int PARTICLE_MAX = 1000;
	PARTICLE m_Particle[PARTICLE_MAX] = {};

	bool m_Mix = false;//加算合成のオンオフ
	float m_Count = 0;
public:
	ParticleEmiter() {};
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;

	virtual void Load(const wchar_t* FileName);

	virtual void LoadParticleTexture();// 子クラスでパーティクルを変更したい時のみ
};