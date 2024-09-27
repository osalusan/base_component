#pragma once
#include "component.h"
#include <iostream>

class TransForm :public Component
{

public:
	using Component::Component;
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_RecordPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 m_Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4 m_Quaternion = { 0.0f,0.0f,0.0f,1.0f };
	void Init()override {};
	void Unit()override {};
	void Update()override {};
	void Draw()override {};

	// ���ω�
	XMFLOAT3 GetAbsPosition() {
		XMVECTOR pos = XMLoadFloat3(&m_Position);
		XMFLOAT3 result;
		XMVECTOR absPos = XMVectorAbs(pos);            // ��Βl���擾
		XMStoreFloat3(&result, absPos);				   //XMFLOAT3�ɕϊ�
		return result;
	}


	// �J�����Ƃ��̃I�u�W�F�N�g�Ԃ̋���/�����ɃJ�����̍��W������
	float CameraDistance(const TransForm p1) {
		return std::sqrt(std::pow(m_Position.x - p1.m_Position.x, 2) +
			std::pow(m_Position.y - p1.m_Position.y, 2) +
			std::pow(m_Position.z - p1.m_Position.z, 2));
	}

	// 2�̃I�u�W�F�N�g�Ԃ̋���
	float ObjectDistance(const TransForm p1, const TransForm p2) {
		return std::sqrt(std::pow(p2.m_Position.x - p1.m_Position.x,2) +
			std::pow(p2.m_Position.y - p1.m_Position.y, 2) +
			std::pow(p2.m_Position.z - p1.m_Position.z, 2));
	}
	// �O���x�N�g���̎擾
	XMFLOAT3 GetForward()
	{
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(
			m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[2]);
		return forward;
	}
	// �O���x�N�g���̎擾
	XMFLOAT3 GetRight()
	{
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(
			m_Rotation.x, m_Rotation.y, m_Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[0]);
		return forward;
	}
	// �ړ�����
	XMFLOAT3 GetDirection(XMFLOAT3 velocity) {
		m_Direction.x = (m_Position.x + velocity.x )- m_Position.x;
		m_Direction.y = (m_Position.y + velocity.y )- m_Position.y;
		m_Direction.z = (m_Position.z + velocity.z )- m_Position.z;
		// �x�N�g���𐳋K��
		XMVECTOR directionVector = XMVector3Normalize(XMLoadFloat3(&m_Direction));
		XMStoreFloat3(&m_Direction, directionVector);
		return m_Direction;
	}

	// �^�[�Q�b�g�Ɍ������x�N�g�����擾
	XMFLOAT3 GetTargetDirection(XMFLOAT3 targetpos) {
		// �x�N�^�[�ɕϊ�
		XMVECTOR myVector = XMLoadFloat3(&m_Position);
		XMVECTOR targetVector = XMLoadFloat3(&targetpos);
	
		XMVECTOR direction = XMVectorSubtract(myVector, targetVector);
		XMVECTOR normalizedDirection = XMVector3Normalize(direction);
		// XMFLOAT3�ɖ߂�
		XMFLOAT3 target;
		XMStoreFloat3(&target, normalizedDirection);

		return target;
	}
};