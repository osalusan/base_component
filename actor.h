#pragma once
#include "gameobj.h"
//components
#include "velocity.h"
#include "sharder.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "billboard.h"
class Actor : public GameObject
{
protected:
	// �R���|�[�l���g
	Velocity* m_Velocity = {};
	Sharder* m_Sharder = {};
	ModelRenderer* m_Model = {};
	AnimationModel* m_AnimeModel = {};

	// �|�C���^�ۑ��p
	BillBoard* m_BillBoard = {};

	//�I�v�V����
	float m_Gravity = -2.0f;
	int m_Count = 0;
public:
	Actor() {}
	virtual void Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void InitComponent()override;
	virtual void UpdateComponent()override;
	virtual void DrawComponent()override;
	virtual void RemoveComponent()override;
	~Actor()override;
	// ------------------ �K�v�ɉ����ăI�[�o�[���C�h ------------------
	virtual void Move() {}// �ړ�����
	virtual void LoadModel();// ���f���̓ǂݍ��ݏ���
	virtual void CollisionControl();// �����蔻��

	// ----------------- �֗��@�\ ------------------
	// ��]�p�̐��`���
	float Lerp_R(float start, float end, float time)
	{
		// �p�x�̍����v�Z
		float difference = fmodf(end - start + DirectX::XM_PI, DirectX::XM_2PI) - DirectX::XM_PI;
		// �p�x����
		return start + time * difference;
	}

};