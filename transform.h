#pragma once
#include "component.h"
#include <iostream>

class TransForm :public Component
{

public:
	using Component::Component;
	XMFLOAT3 _Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 _RecordPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 _Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 _Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 _Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4 _Quaternion = { 0.0f,0.0f,0.0f,1.0f };
	void Init()override {};
	void Unit()override {};
	void Update()override {};
	void Draw()override {};

	// 平均化
	XMFLOAT3 GetAbsPosition() {
		XMVECTOR pos = XMLoadFloat3(&_Position);
		XMFLOAT3 result;
		XMVECTOR absPos = XMVectorAbs(pos);            // 絶対値を取得
		XMStoreFloat3(&result, absPos);				   //XMFLOAT3に変換
		return result;
	}


	// カメラとこのオブジェクト間の距離/引数にカメラの座標を入れる
	float CameraDistance(const TransForm p1) {
		return std::sqrt(std::pow(_Position.x - p1._Position.x, 2) +
			std::pow(_Position.y - p1._Position.y, 2) +
			std::pow(_Position.z - p1._Position.z, 2));
	}

	// 2つのオブジェクト間の距離
	float ObjectDistance(const TransForm p1, const TransForm p2) {
		return std::sqrt(std::pow(p2._Position.x - p1._Position.x,2) +
			std::pow(p2._Position.y - p1._Position.y, 2) +
			std::pow(p2._Position.z - p1._Position.z, 2));
	}
	// 前方ベクトルの取得
	XMFLOAT3 GetForward()
	{
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(
			_Rotation.x, _Rotation.y, _Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[2]);
		return forward;
	}
	// 前方ベクトルの取得
	XMFLOAT3 GetRight()
	{
		XMMATRIX rotationMatrix;
		rotationMatrix = XMMatrixRotationRollPitchYaw(
			_Rotation.x, _Rotation.y, _Rotation.z);

		XMFLOAT3 forward;
		XMStoreFloat3(&forward, rotationMatrix.r[0]);
		return forward;
	}
	// 移動方向
	XMFLOAT3 GetDirection(XMFLOAT3 velocity) {
		_Direction.x = (_Position.x + velocity.x )- _Position.x;
		_Direction.y = (_Position.y + velocity.y )- _Position.y;
		_Direction.z = (_Position.z + velocity.z )- _Position.z;
		// ベクトルを正規化
		XMVECTOR directionVector = XMVector3Normalize(XMLoadFloat3(&_Direction));
		XMStoreFloat3(&_Direction, directionVector);
		return _Direction;
	}

	// ターゲットに向かうベクトルを取得
	XMFLOAT3 GetTargetDirection(XMFLOAT3 targetpos) {
		// ベクターに変換
		XMVECTOR myVector = XMLoadFloat3(&_Position);
		XMVECTOR targetVector = XMLoadFloat3(&targetpos);
	
		XMVECTOR direction = XMVectorSubtract(myVector, targetVector);
		XMVECTOR normalizedDirection = XMVector3Normalize(direction);
		// XMFLOAT3に戻す
		XMFLOAT3 target;
		XMStoreFloat3(&target, normalizedDirection);

		return target;
	}
};