#include "firepillar.h"
#include "manager.h"

void FirePillar::Init()
{
	Actor::Init();
	m_TransForm->m_Scale = { 10.0f,10.0f,10.0f };
	//Manager::GetScene()->AddGameObject_T<BlueFire>(Draw_Effect)->m_TransForm->m_Position = {m_TransForm->m_Position.x ,m_TransForm->m_Position.y + (m_TransForm->m_Scale.y *0.9f) , m_TransForm->m_Position.z};
	//Manager::GetScene()->AddGameObject_T<BlueFirem_BillBoard>(Draw_Effect)->SetBillBoard({ m_TransForm->m_Position.x,m_TransForm->m_Position.y + m_TransForm->m_Scale.y * 0.5f,m_TransForm->m_Position.z }, m_TransForm->m_Scale);
}
