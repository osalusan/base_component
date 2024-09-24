#include "playerattack.h"
#include "enemybase.h"
#include "manager.h"
#include "enemy_skull.h"

void PlayerPunchi::LoadModel()
{
	_Model = new ModelRenderer(this);
	_Model->Init();
	_Model->Load("asset\\model\\head.obj"); 
	_Collision = new Collision(this);
	_Collision->Init();
	_TransForm->_Scale = { 4.0f,4.0f,4.0f };
	_Model->_visible = false;
}


void PlayerPunchi::CollisionControl()
{
	_Collision->Update();
	if (_Collision->_hit || _Collision->_groundHit ) {
		if(_Collision->_otherActor == Manager::GetScene()->GetGameObject<Enemy_Skull>())Manager::GetScene()->GetGameObject<Enemy_Skull>()->_hp -= 10.0f; Manager::GetScene()->GetPlayerCharcter()->_atkFlag = false;
	}
}
