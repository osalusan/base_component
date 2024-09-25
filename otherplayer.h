#pragma once
#include "player.h"
class OtherPlayer :public GameObject {
private:
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};

	//�O�F���@�P�F�́@�Q�F����@�R�F�E��@�S�F�����@�T�F�E��
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