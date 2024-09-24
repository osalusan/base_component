#pragma once
#include "gameobj.h"
#include "velocity.h"
#include "modelRenderer.h"
#include "sharder.h"
#include "animation.h"
#include "job.h"
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
	Velocity* _Velocity = {};
	Sharder* _Sharder = {};
	Collision* _Collision = {};
	AnimationModel* _animeModel = {};
	Audio* _attackSE = {};

	Job* _job = {};

	float _moveSpeed = 15.00f;
	bool _dash = false;			  // �_�b�V����
	bool _jump = false;			  // �W�����v��
	bool _chengeAnimation = false;// �A�j���[�V���������ς����邩�ǂ���
	int _animationFrame = 0;	  // �A�j���[�V�����̃t���[��
	std::string _animationName = "Idle";// �A�j���[�V�����̖��O
	std::string _nextanimationName = "Idle";// �u�����h�p�A���̃A�j���[�V�����̖��O
	float _blendRatio = 1.0f;// �A�j���[�V�����u�����h�̐��l
	bool _useAttack = false;

	float _lerpValue = 0;


	int _atkCount = 0;
	int _atkTime = 100.0f;
	int _dashCount = 0;
	
public:
	bool _atkFlag = false;// �U������������
	float _hp = 100.0f;// �̗�
	float _stamina = 100.0f;// �X�^�~�i

	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
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