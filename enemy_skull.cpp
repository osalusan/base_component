#include "enemy_skull.h"
#include "manager.h"
#include "fire.h"
#include "skull_attack.h"
void Enemy_Skull::LoadModel()
{
	_TransForm->_Scale = { 5.0f,5.0f,5.0f };
	_Model = new ModelRenderer(this);
	_Model->Init();
	_Model->Load("asset\\model\\skull_downloadable.obj"); 
	_hp = 155.0f;
}

//void Enemy_Skull::Move()
//{
//
//
//}

void Enemy_Skull::SetMaxPaturn()
{
	_atkMax = Atk_Max;
	_moveMax = Move_Max;
	_downMax = Down_Max;
	_idleMax = Idle_Max;
}

void Enemy_Skull::StateControl()
{
	//switch (_state)
	//{
	//case ENEMY_STATE::Enemy_Idel:
	//	
	//	break;
	//case ENEMY_STATE::Enemy_Search:

	//	break;
	//case ENEMY_STATE::Enemy_Move:
	//	
	//	break;
	//case ENEMY_STATE::Enemy_Attack:

	//	break;
	//case ENEMY_STATE::Enemy_Stagger:

	//	break;
	//case ENEMY_STATE::Enemy_Down:

	//	break;
	//default:
	//	break;
	//}

	//_hp--;
	// スタン
	if (_stanValue >= 50.0f)
	{

	}
	if (_rotate >= 6.28f) { _rotate -= 6.28f; _rotate = _rotate - 6.28f; }
}

void Enemy_Skull::StateIdel()
{
	//SetDebugState(ENEMY_STATE::Enemy_Attack, 3);
	RotationPlayer();
	if (_count >= 20) { _Animation->_loop = false; _Animation->SetFloatData(90.0f, 0.15f, 0.0f); _TransForm->_Position.y += _Animation->AnimationFloat(); }
	//if (_count == 160) { Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect)->_TransForm->_Position = _TransForm->_Position; }
	if (_count >= 260) { SetRandState(); } // 待機終了
}

void Enemy_Skull::StateSearch()
{

}

void Enemy_Skull::StateMove()
{
	switch (_paturnNo) {
	case Move_Back:
		RotationPlayer();
		if (_count <= 20) { _Velocity->_Velocity = { -_TransForm->GetForward().x * 0.1f ,0.0f,-_TransForm->GetForward().z * 0.1f }; }
		if (_count >= 110) { SetRandState(); }
		break;
	case Move_Right:
	{
		RotationPlayer();// _Velocity->_Velocity = _TransForm->GetRight();
		_rotate += 0.045f;
		float size = 40.0f;
		_TransForm->_Position = { _player->_TransForm->_Position.x - sinf(_rotate) * size , 0.0f, _player->_TransForm->_Position.z + cosf(_rotate) * size };
		if (_count >= 130) { SetRandState(); }
	}
		break;
	case Move_Stop:
		if (_count >= 130) { SetRandState(); }
		_Velocity->_Velocity = { 0.0f,0.0f,0.0f };
		RotationPlayer();
		break;
	default:
		break;
	}

}

void Enemy_Skull::StateAttack()
{
	switch (_paturnNo) {
	case Atk_Takkel: // プレイヤーに向かって突進/周囲に炎を展開
		_Animation->_loop = false;
		if (_count == 1) { Manager::GetScene()->AddGameObject_T<Skull_Sphere>(Draw_Actor)->SetEnemyPointer(this); _TransForm->_Position.y = 0.0f; }
		if (_count <= 70) {
			RotationPlayer(); _Velocity->_Velocity.x = -_TransForm->GetForward().x * 0.3f; _Velocity->_Velocity.z = -_TransForm->GetForward().z * 0.3f;
			_Animation->SetFloatData(50.0f, 0.15f, 0.0f); _Velocity->_Velocity.y = _Animation->AnimationFloat();
		}
		if (_count >= 80 && _count <= 170) { _Velocity->_Velocity = _TransForm->GetForward(); _Animation->SetFloatData(50.0f, 0.15f, 0.0f); _Velocity->_Velocity.y = -_Animation->AnimationFloat(); }
		if (_count >= 220) { SetRandState(); }
		break;

	case Atk_RoringFireBullet: // プレイヤーの周りを旋回しながら攻撃
		RotationPlayer(); _Velocity->_Velocity = _TransForm->GetRight();
		_TransForm->_Position.y = 0.0f;
		if (_count >= 260) { SetRandState(); }
		else {
			int bullet= _count / 30;
			if (bullet < 1) { bullet = 1; }
			if (_count == 30 * bullet || _count ==  (30 * bullet) + 3 || _count == (30 * bullet) + 6) {Manager::GetScene()->AddGameObject_T<Skull_FireBullet>(Draw_Actor)->SetEnemyPointer(this); }
		}
		break;
	case Atk_Fall:
	{
		float toll = 30.0f;
		if (_count >= 420) { SetRandState(); }
		if (_count == 1 || _count == 111) { Manager::GetScene()->AddGameObject_T<Skull_Fall>(Draw_Actor)->SetEnemyPointer(this); }
		if (_count <= 60) { _TransForm->_Position.x = _player->_TransForm->_Position.x; _TransForm->_Position.y = _player->_TransForm->_Position.y + toll; _TransForm->_Position.z = _player->_TransForm->_Position.z; }
		if (_count >= 110 && _count <= 160) { _TransForm->_Position.x = _player->_TransForm->_Position.x; _TransForm->_Position.y = _player->_TransForm->_Position.y + toll; _TransForm->_Position.z = _player->_TransForm->_Position.z; }
		if (_count <= 200) { 
			if (_TransForm->_Position.y >= 0.0f) { _Velocity->_Velocity.y = -1.5f; } 
			else { _Velocity->_Velocity.y = 0.0f; }
		}
		if (_count >= 200 && _count <= 240) { RotationPlayer(); _Velocity->_Velocity.x = -_TransForm->GetForward().x * 0.3f; _Velocity->_Velocity.z = -_TransForm->GetForward().z * 0.3f; }
		else { _Velocity->_Velocity.x = 0.0f;  _Velocity->_Velocity.z = 0.0f; }
	}
		break;
	default:
		break;
	case Atk_Beam:
		if (_count >= 520) { SetRandState(); _TransForm->_Rotation.x = 0.0f; }
		else {_Velocity->_Velocity = { 0.0f,0.0f,0.0f };}
		if (_count == 300) { _TransForm->_Rotation.x = 0.7f; }
		if (_count == 1) { Manager::GetScene()->AddGameObject_T<Skull_Beam>(Draw_Actor)->SetEnemyPointer(this); }
		if (_count <= 100) { RotationPlayer(); }
		break;
	}
}

void Enemy_Skull::StateStagger()
{

}

void Enemy_Skull::StateDown()
{

}

