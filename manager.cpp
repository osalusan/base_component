
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
#include "fade.h"
#include "result.h"
#include "gameclear.h"
#include "gameover.h"
#define PORT (8888)
const std::string serverIP = "192.168.11.32";
#if _DEBUG

#endif


Scene* Manager::m_Scene;
Scene* Manager::m_NextScene;
Audio* Manager::m_Audio;
UDP_Server* Manager::m_UDPServer;
UDP_Client* Manager::m_UDPClient;
int Manager::m_Players;
int Manager::m_ConnectionCount;

Fade* Manager::m_Fade;
void Manager::Init()
{
	Renderer::Init();
	m_ConnectionCount = 0;
	m_Audio->InitMaster();
	m_Scene = new Title;
	m_Scene->Init();
	m_Fade = new Fade;
	m_Fade->Init();
}


void Manager::Uninit()
{
	if (m_UDPClient) {delete m_UDPClient;}
	if (m_UDPServer) { RemoveServer(); }
	
	m_Fade->Uninit();
	delete m_Fade;
	m_Scene->Uninit();
	delete m_Scene;

	ModelRenderer::UnloadAll();
	Audio::UninitMaster();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();


	if (!m_Fade->_used) { m_Scene->Update(); m_Fade->_alfa = 0.0f; }
	else { m_Fade->Update(); }


	//if (Input::GetKeyTrigger('0'))
	//{
	//	if (!m_UDPServer)
	//	{
	//		m_UDPServer = new UDP_Server;
	//	}
	//}
	
	//if (Input::GetKeyTrigger('3'))
	//{
	//	GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = m_Players;
	//}

	//if (Input::GetKeyTrigger(VK_RETURN)) {
	//	if (!m_UDPClient) {
	//		 m_UDPClient = new UDP_Client(serverIP, PORT);
	//	}
	//}

	// Ú‘±Šm”F
	if (m_UDPClient && !m_UDPClient->_Success) {m_UDPClient->Check();}
	// Ú‘±¬Œ÷
	if (m_UDPClient) { m_UDPClient->Success(); }
}

void Manager::Draw()
{

	Renderer::Begin();

	m_Scene->Draw();

	m_Fade->Draw();

	Renderer::End();

	if (m_NextScene)
	{
		m_Fade->StartFadeIn();
		if (!m_Fade->_used)
		{
			if (m_Scene)
			{
				m_Scene->Uninit();
				delete m_Scene;
				m_Audio->UninitMaster();
			}
			m_Audio->InitMaster();
			m_Scene = m_NextScene;
			m_Scene->Init();

			m_NextScene = nullptr;
			m_Fade->StartFadeOut();
			m_Scene->Update();
		}
	}
}

void Manager::CreateServer()
{
	if (!m_UDPServer) { m_UDPServer = new UDP_Server; }
}

void Manager::RemoveServer()
{
	if (m_UDPServer) { 
		m_UDPServer->Stop(); delete m_UDPServer; m_UDPServer = nullptr;
	}
}

void Manager::Disconnect()
{
	m_Players--;
}

void Manager::AddOtherPlayer(int count)
{
	if (m_Players >= 0 && m_Players < MAX_PLAYERS)
	{
		m_Players = count;
		GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = m_Players;	
	}
		
}

void Manager::AddOtherClientPlayers(int id)
{
	if (m_Players >= 0 && m_Players < MAX_PLAYERS)
	{
		GetScene()->AddGameObject_T<OtherPlayer>(Draw_Actor)->playerID = id;
	}
}

void Manager::AddConnectionCount()
{
	m_ConnectionCount++;
	if (m_ConnectionCount > 500)
	{
		RemoveClient();
		ResetConnectionCound();
	}
}
