#pragma once
#include "gameobj.h"
#include "velocity.h"
#include "modelRenderer.h"
#include "sharder.h"
#include "animation.h"
#include "collision.h"
#include "animationModel.h"
#include "audio.h"

#define DISTANCE_HAND (1.7f)	//��Ƒ̂̋���
#define DISTANCE_LEG (0.7f)
#define MAX_PARTS (6)				//�p�[�c�̕�����

enum class PLAYER_STATE {
	PLAYER_IDEL =0,
	PLAYER_WALK,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_ATTACK,
	PLAYER_AVOIDANCE,
	PLAYER_GARD,
	PLAYER_DOWN,
	PLAYER_MAX

};

//�Q�X�g����󂯎��p�̍\����
typedef struct OtherPlayerData {
	int playerID = 0;
	PLAYER_STATE playerState;
	XMFLOAT3 pos = {};
};
class Player :public GameObject {
private:
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};
	Collision* m_Collision = {};
	AnimationModel* m_AnimeModel = {};
	ModelRenderer* m_ChildModel = {};
	Audio* m_AttackSE = {};


	float m_MoveSpeed = 15.00f;
	bool m_Dash = false;			  // �_�b�V����
	bool m_Jump = false;			  // �W�����v��
	bool m_ChengeAnimation = false;// �A�j���[�V���������ς����邩�ǂ���
	unsigned int m_AnimationFrame = 0;	  // �A�j���[�V�����̃t���[��
	std::string m_AnimationName = "Idle";// �A�j���[�V�����̖��O
	std::string m_NextanimationName = "Idle";// �u�����h�p�A���̃A�j���[�V�����̖��O
	float m_BlendRatio = 1.0f;// �A�j���[�V�����u�����h�̐��l
	bool m_UseAttack = false;

	float _lerpValue = 0;


	int m_AtkCount = 0;
	int m_AtkTime = 100.0f;
	int m_DashCount = 0;
	
public:
	bool m_AtkFlag = false;// �U������������
	float m_Hp = 100.0f;// �̗�
	float m_Stamina = 100.0f;// �X�^�~�i

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponents()override;
	virtual void UpdateComponents()override;
	virtual void DrawComponents()override;
	virtual void RemoveComponents()override;
	void Move();
	void CollisionControl();
	void AnimationState();
	void SetState(std::string state);
	void Attack();
	void LoadModel();

	// ----------------- �֗��@�\ ------------------
	// ��]�p�̐��`���
	float Lerp_R(float start, float end, float time)
	{
		// �p�x�̍����v�Z
		float difference = fmodf(end - start + XM_PI, XM_2PI) - XM_PI;
		// �p�x����
		return start + time * difference;
	}
};