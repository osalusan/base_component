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
	static Scene* _Scene;
	static Scene* _NextScene;
	static Audio* _Audio;
	static UDP_Server* _UDPServer;
	static UDP_Client* _UDPClient;
	static int _Players;
	static int _ConnectionCount;
	static JOB _useJob;
	static Fade* _fade;
public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() { return _Scene; }
	static UDP_Server* GetUDPServer() { return _UDPServer; }
	static UDP_Client* GetUDPClient() { return _UDPClient; }
	static void CreateServer();
	static void RemoveServer();
	static int GetClientPlayer() { return _Players; }
	static void Disconnect();
	static void RemoveClient() {
		delete _UDPClient; _UDPClient = nullptr;
	}

	template<typename T>
	static void SetScene()
	{
		if (_NextScene)
		{
			delete _NextScene;
			_NextScene = new T;
		}
		else if (!_NextScene) _NextScene = new T;
	}
	static void ResetConnectionCound() { _ConnectionCount = 0; }
	static void AddOtherPlayer(int count);
	static void AddOtherClientPlayers(int id);
	static void AddConnectionCount();
	static JOB GetUseJob() {return _useJob;}
	static void SetUseJob(JOB job) { _useJob = job; }

	static int GetRandom(int num) {
		return std::rand() % num;  // 0‚©‚çnum - 1‚Ü‚Å‚Ì”ÍˆÍ
	};
};