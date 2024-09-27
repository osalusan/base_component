#include "network.h"
#include "manager.h"
#include "player_camera.h"
#include "player.h"
#include "game_skydome.h"
#include "udp_client.h"
#include "udp_server.h"
#include "otherplayer.h"
void Network::Init()
{ 
	AddGameObject<Player_Camera>(Draw_Camera)->m_TransForm->m_Position = { 0.0f,4.0f, -10.0f };
	AddGameObject<Game_SkyDome>(Draw_SkyDome);
	AddGameObject<Player>(Draw_Actor);

	Scene::Init();
}

