
#include "manager.h"
#include "scene.h"
#include "udp_server.h"
#include "udp_client.h"
#include "game.h"
#include "title.h"
#include "modelRenderer.h"
#include "audio.h"
#include "input.h"
#include "network.h"
#include "otherplayer.h"
#include "job.h"
#include "fade.h"
#include "result.h"
#include "gameclear.h"
#include "gameover.h"
#define PORT (8888)
const std::string serverIP = "192.168.11.32";
#if _DEBUG

#endif


Scene* Manager::_Scene;
Scene* Manager::_NextScene;
Audio* Manager::_Audio;
UDP_Server* Manager::_UDPServer;
UDP_Client* Manager::_UDPClient;
int Manager::_Players;
int Manager::_ConnectionCount;
JOB Manager:: _useJob;
Fade* Manager::_fade;
void Manager::Init()
{
	Renderer::Init();
	_useJob = JOB::Job_Swordsman;
	_ConnectionCount = 0;
	_Audio->InitMaster();
	_Scene = new Game;
	_Scene->Init();
	_fade = new Fade;
	_fade->Init();
	//ランダム値の初期化
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}


void Manager::Uninit()
{
	if (_UDPClient) {delete _UDPClient;}
	if (_UDPServer) { RemoveServer(); }
	
	_fade->Uninit();
	delete _fade;
	_Scene->Uninit();
	delete _Scene;

	ModelRenderer::UnloadAll();
	Audio::UninitMaster();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();


	if (!_fade->_used) { _Scene->Update(); _fade->_alfa = 0.0f; }
	else { _fade->Update(); }


	//if (Input::GetKeyTrigger('0'))
	//{
	//	if (!_UDPServer)
	//	{
	//		_UDPServer = new UDP_Server;
	//	}
	//}
	
	//if (Input::GetKeyTrigger('3'))
	//{
	//	GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = _Players;
	//}

	//if (Input::GetKeyTrigger(VK_RETURN)) {
	//	if (!_UDPClient) {
	//		 _UDPClient = new UDP_Client(serverIP, PORT);
	//	}
	//}

	// 接続確認
	if (_UDPClient && !_UDPClient->_Success) {_UDPClient->Check();}
	// 接続成功
	if (_UDPClient) { _UDPClient->Success(); }
}

void Manager::Draw()
{

	Renderer::Begin();

	_Scene->Draw();

	_fade->Draw();

	Renderer::End();

	if (_NextScene)
	{
		_fade->StartFadeIn();
		if (!_fade->_used)
		{
			if (_Scene)
			{
				_Scene->Uninit();
				delete _Scene;
				_Audio->UninitMaster();
			}
			_Audio->InitMaster();
			_Scene = _NextScene;
			_Scene->Init();

			_NextScene = nullptr;
			_fade->StartFadeOut();
			_Scene->Update();
		}
	}
}

void Manager::CreateServer()
{
	if (!_UDPServer) { _UDPServer = new UDP_Server; }
}

void Manager::RemoveServer()
{
	if (_UDPServer) { 
		_UDPServer->Stop(); delete _UDPServer; _UDPServer = nullptr;
	}
}

void Manager::Disconnect()
{
	_Players--;
}

void Manager::AddOtherPlayer(int count)
{
	if (_Players >= 0 && _Players < MAX_PLAYERS)
	{
		_Players = count;
		GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = _Players;	
	}
		
}

void Manager::AddOtherClientPlayers(int id)
{
	if (_Players >= 0 && _Players < MAX_PLAYERS)
	{
		GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = id;
	}
}

void Manager::AddConnectionCount()
{
	_ConnectionCount++;
	if (_ConnectionCount > 500)
	{
		RemoveClient();
		ResetConnectionCound();
	}
}
