#include "scene.h"
#include "loading.h"
#include "loadLogo.h"
#include "title_camera.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include <thread>

void Loading::Init()
{
	AddGameObject<Title_Camera>(Draw_Camera)->m_TransForm->m_Position = { 0.0f,5.0f, -10.0f };
	AddGameObject<LoadLogo>(Draw_Polygon2D)->SetSize({ SCREEN_WIDTH * 0.85f,SCREEN_HEIGHT * 0.85f,0.0f }, { SCREEN_WIDTH * 0.2f,SCREEN_HEIGHT * 0.2f,0.0f }, 0);
	Scene::Init();

	std::thread th(&Game::Load); // ƒXƒŒƒbƒh
	th.detach();
}

void Loading::Update()
{
	Scene::Update();
	if (Game::GetLoadFinish())
	{
		Manager::SetScene<Game>();
	}
}

