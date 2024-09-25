#include "firepillar.h"
#include "manager.h"

void FirePillar::Init()
{
	Actor::Init();
	_TransForm->_Scale = { 10.0f,10.0f,10.0f };
	//Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect)->_TransForm->_Position = {_TransForm->_Position.x ,_TransForm->_Position.y + (_TransForm->_Scale.y *0.9f) , _TransForm->_Position.z};
	//Manager::GetScene()->AddGameObject_T<BlueFirem_BillBoard>(Draw_Effect)->SetBillBoard({ _TransForm->_Position.x,_TransForm->_Position.y + _TransForm->_Scale.y * 0.5f,_TransForm->_Position.z }, _TransForm->_Scale);
}
