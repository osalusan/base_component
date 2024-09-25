#pragma once
#include "player.h"
class OtherPlayer :public GameObject {
private:
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};

	//０：頭　１：体　２：左手　３：右手　４：左足　５：右足
	ModelRenderer* _partsModel[MAX_PARTS] = {};
	TransForm* _partsTransFomr[MAX_PARTS] = {};
	Animation* _partsAnimation[MAX_PARTS] = {};

public:
	int playerID = 0;
	PLAYER_STATE _state = PLAYER_STATE::PLAYER_MAX;
	OtherPlayer() {};
	virtual ~OtherPlayer() {};
	void LoadModel();
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;

	void SetState(PLAYER_STATE state);
	void AnimationState();
};