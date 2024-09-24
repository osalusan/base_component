
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "gameobj.h"
#include "skydome.h"
#include "transform.h"

void Scene::Init()
{
	for (int i = 0; i < Draw_Max; i++)
	{
		for (auto GameObj : _GameObjects[i]) {
			GameObj->Init();
			_player = GetGameObject<Player>();
		}
	}
}

void Scene::Uninit()
{
	for (int i = 0; i < Draw_Max; i++)
	{
		for (auto GameObj : _GameObjects[i]) {
			GameObj->Uninit();
		}
	}
	for (int i = 0; i < Draw_Max; i++)
	{
		for (auto it = _GameObjects[i].begin(); it != _GameObjects[i].end(); ) {
			delete* it;
			it = _GameObjects[i].erase(it);
		}
	}
}

void Scene::Update()
{
	for (int i = 0; i < Draw_Max; i++)
	{
		for (auto GameObj : _GameObjects[i]) {
			GameObj->Update();
		}
	}
}

void Scene::Draw()
{
	for (int i = 0; i < Draw_Max; i++)
	{
		for (auto GameObj : _GameObjects[i]) {
			GameObj->Draw();
		}
	}
}
// ƒvƒŒƒCƒ„[‚Ìæ“¾
Player *  Scene::GetPlayerCharcter()
{
	return _player;
}
