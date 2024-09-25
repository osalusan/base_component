#include "manager.h"
#include "player.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "player_camera.h"
void Player_Camera::Init()
{
	if(_Player = Manager::GetScene()->GetGameObject<Player>());

	Camera::Init();
}
void Player_Camera::Update()
{
	/*SetTarget(Manager::GetScene()->GetGameObject<Player>()->m_TransForm->_Position);*/
	POINT MousePos{};
	GetCursorPos(&MousePos);

	_MousePos = XMFLOAT2(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y));


#if _DEBUG
	if (Input::GetKeyPress('R'))
	{
		SetCursorPos(GetWindowSize().x * 0.5f, GetWindowSize().y * 0.5f);
		_OldMousePos = _MousePos;
	}

	//if (_MousePos.x <= 100.0f || _MousePos.x >= GetWindowSize().x - 100.0f || _MousePos.y <= 100.0f || _MousePos.y >= GetWindowSize().y - 100.0f)
	//{
	//	SetCursorPos(GetWindowSize().x * 0.5f, GetWindowSize().y * 0.5f);
	//	GetCursorPos(&MousePos);
	//	_MousePos = XMFLOAT2(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y));
	//	_OldMousePos = _MousePos;
	//}
#else
	if (_MousePos.x <= 100.0f || _MousePos.x >= GetWindowSize().x - 100.0f || _MousePos.y <= 100.0f || _MousePos.y >= GetWindowSize().y - 100.0f)
	{
		SetCursorPos(GetWindowSize().x * 0.5f, GetWindowSize().y * 0.5f);
		POINT MousePos{};
		GetCursorPos(&MousePos);
		_MousePos = XMFLOAT2(static_cast<float>(MousePos.x), static_cast<float>(MousePos.y));
		_OldMousePos = _MousePos;
	}
#endif // _DEBUG

	//マウスの横移動処理
	m_TransForm->_Rotation.y += (_MousePos.x - _OldMousePos.x) * 0.005f;
	//マウスの縦移動処理
	m_TransForm->_Rotation.x -= (_MousePos.y - _OldMousePos.y) * 0.005f;
	//マウスの上下制限
	if (m_TransForm->_Rotation.x > 1.14f)m_TransForm->_Rotation.x = 1.14f;
	if (m_TransForm->_Rotation.x < -1.14f)m_TransForm->_Rotation.x = -1.14f;

	if(_Player !=nullptr)_Target = _Player->m_TransForm->_RecordPosition;

	//カメラの移動処理
	m_TransForm->_Position.x = _Target.x - sinf(m_TransForm->_Rotation.y) * _length;
	m_TransForm->_Position.z = _Target.z - cosf(m_TransForm->_Rotation.y) * _length;

	m_TransForm->_Position.y = _Target.y - sinf(m_TransForm->_Rotation.x) * _length;


	_OldMousePos = _MousePos;
	Camera::Update();
}
