#include "gameover.h"
#include "scene.h"
#include "title.h"
#include "title_skydome.h"
#include "title_camera.h"
#include "resultbackground.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "title_background.h"

void GameOver::Init()
{
	AddGameObject<Title_Camera>(Draw_Camera)->m_TransForm->_Position = { 0.0f,5.0f, -10.0f };
	AddGameObject<Title_SkyDome>(Draw_SkyDome);
	AddGameObject<Result_Over>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.2f,0.0f }, { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.2f,0.0f }, 0);
	AddGameObject<Result_Select>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.5f,0.0f }, { SCREEN_WIDTH * 0.32f,SCREEN_HEIGHT * 0.17f,0.0f }, 0);
	AddGameObject<Result_BackTitle>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.7f,SCREEN_HEIGHT * 0.5f,0.0f }, { SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.15f,0.0f }, 0);
	AddGameObject<Result_Retry>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.5f,0.0f }, { SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.15f,0.0f }, 0);
	AddGameObject<Title_Enter>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.9f,0.0f }, { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.1f,0.0f }, 0);

	Scene::Init();
}

void GameOver::Update()
{
	Scene::Update();
	if (Input::GetKeyPress('A')) { _select = 1; }
	if (Input::GetKeyPress('D')) { _select = 2; }

	if (_select == 1) { Manager::GetScene()->GetGameObject<Result_Select>()->SetSize({ SCREEN_WIDTH * 0.3f,SCREEN_HEIGHT * 0.5f,0.0f }, { SCREEN_WIDTH * 0.32f,SCREEN_HEIGHT * 0.17f,0.0f }, 0); }
	if (_select == 2) { Manager::GetScene()->GetGameObject<Result_Select>()->SetSize({ SCREEN_WIDTH * 0.7f,SCREEN_HEIGHT * 0.5f,0.0f }, { SCREEN_WIDTH * 0.32f,SCREEN_HEIGHT * 0.17f,0.0f }, 0); }
	if (Input::GetKeyRelease(VK_SPACE))
	{
		if (_select == 1) { Manager::SetScene<Game>(); }
		if (_select == 2) { Manager::SetScene<Title>(); }

	}
}
