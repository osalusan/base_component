#include "scene.h"
#include "title.h"
#include "title_skydome.h"
#include "title_camera.h"
#include "title_background.h"
#include "manager.h"
#include "input.h"
#include "game.h"
void Title::Init()
{
	AddGameObject<Title_Camera>(Draw_Camera)->m_TransForm->m_Position = {0.0f,5.0f, -10.0f };
	AddGameObject<Title_SkyDome>(Draw_SkyDome);
	AddGameObject<Title_BackGround>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.3f,0.0f }, { SCREEN_WIDTH * 0.7f,SCREEN_HEIGHT * 0.3f,0.0f }, 0);
	AddGameObject<Title_Enter>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9f,0.0f }, { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.1f,0.0f }, 0);


	Scene::Init();
}

void Title::Update()
{
	Scene::Update();
	if (Input::GetKeyRelease(VK_SPACE))
	{
		Manager::SetScene<Game>();
	}
}
