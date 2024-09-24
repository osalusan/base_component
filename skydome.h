#pragma once
#include "gameobj.h"
#include "sharder.h"
#include "modelRenderer.h"
class SkyDome: public GameObject
{
protected:
	Sharder* _Sharder{};
	ModelRenderer* _ModelRenderer{};
public:
	SkyDome() {}
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	virtual void LoadSkyDome();
	virtual void LoadTextureSkyDome();
};