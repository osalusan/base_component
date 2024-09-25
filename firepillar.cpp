#include "firepillar.h"
#include "manager.h"

void FirePillar::Init()
{
	Actor::Init();
	m_TransForm->_Scale = { 10.0f,10.0f,10.0f };
	//Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect)->m_TransForm->_Position = {m_TransForm->_Position.x ,m_TransForm->_Position.y + (m_TransForm->_Scale.y *0.9f) , m_TransForm->_Position.z};
	//Manager::GetScene()->AddGameObject_T<BlueFirem_BillBoard>(Draw_Effect)->SetBillBoard({ m_TransForm->_Position.x,m_TransForm->_Position.y + m_TransForm->_Scale.y * 0.5f,m_TransForm->_Position.z }, m_TransForm->_Scale);
}
