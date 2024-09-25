#pragma once
#include "gameobj.h"
#include "sharder.h"
#include "modelRenderer.h"
class SkyDome: public GameObject
{
protected:
	Sharder* m_Sharder{};
	ModelRenderer* m_ModelRenderer{};
public:
	SkyDome() {}
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	virtual void LoadSkyDome();
	virtual void LoadTextureSkyDome();
};