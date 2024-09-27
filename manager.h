#pragma once
#include <list>
class Scene;
class Audio;
class UDP_Server;
class UDP_Client;
class GameObject;
enum class JOB;
class Fade;
class Manager
{
private:
	static Scene* m_Scene;
	static Scene* m_NextScene;
	static Audio* m_Audio;
	static UDP_Server* m_UDPServer;
	static UDP_Client* m_UDPClient;
	static int m_Players;
	static int m_ConnectionCount;
	static Fade* m_Fade;
public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return m_Scene; }
	static UDP_Server* GetUDPServer() { return m_UDPServer; }
	static UDP_Client* GetUDPClient() { return m_UDPClient; }
	static void CreateServer();
	static void RemoveServer();
	static int GetClientPlayer() { return m_Players; }
	static void Disconnect();
	static void RemoveClient() {
		delete m_UDPClient; m_UDPClient = nullptr;
	}

	template<typename T>
	static void SetScene()
	{
		if (m_NextScene)
		{
			delete m_NextScene;
			m_NextScene = new T;
		}
		else if (!m_NextScene) m_NextScene = new T;
	}
	static void ResetConnectionCound() { m_ConnectionCount = 0; }
	static void AddOtherPlayer(int count);
	static void AddOtherClientPlayers(int id);
	static void AddConnectionCount();

	static int GetRandom(int num) {
		return std::rand() % num;  // 0‚©‚çnum - 1‚Ü‚Å‚Ì”ÍˆÍ
	};
};