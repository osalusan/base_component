
#include "gameobj.h"
#include "game_skydome.h"
#include "title_skydome.h"
#include "transform.h"
#include "player.h"
#include "player_camera.h"
#include "game.h"
#include "manager.h"
#include "enemybase.h"
#include "title_background.h"
#include "enemy_skull.h"
#include "firepillar.h"
#include "fire.h"
#include "billboard.h"
#include "bluefireBillboard.h"
#include "input.h"
#include "gameover.h"
#include "gameclear.h"
void Game::Init()
{

	AddGameObject<Player_Camera>(Draw_Camera)->_TransForm->_Rotation = { 0.0f,0.0f,0.0f };
	AddGameObject<Game_SkyDome>(Draw_SkyDome);
	AddGameObject<Player>(Draw_Actor)->_TransForm->_Position = {0.0f,0.0f,40.0f};
	AddGameObject<Enemy_Skull>(Draw_Actor)->_TransForm->_Position = { 0.0f,0.0f, 5.0f };
	//AddGameObject<BlueFire_Ring>(Draw_Effect)->_TransForm->_Position = { 0.0f,0.0f,15.0f };
	//AddGameObject<BillBoard>(Draw_BillBoard)->SetBillBoard(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 0.0f));
	int maxPillar = 8;
	for (int i = 0; i < maxPillar; i++)
	{
		float distance = 6.28f / maxPillar;
		float pos = maxPillar * i;
		float size = 200.0f;
		AddGameObject<FirePillar>(Draw_Actor)->_TransForm->_Position = { -sinf(pos) * size,10.0f,cosf(pos) * size};
	}
	
	//AddGameObj(new UI(XMFLOAT3(0.0f, 0.0f, 0.0f)));
	Scene::Init();
}

void Game::Update()
{
	Scene::Update();

	//auto& keyboard = Keyboard::GetInstance();
	//if (keyboard.GetKeyRelease(VK_RETURN))	Manager::SetScene<Result>();

	////Zバッファの描画順に使う処理
	//static TransForm* transformPtr = GetGameObject<Camera>()->GetComponent<TransForm>();

	//TransForm& cameratransform = *transformPtr;

#if _DEBUG
	if (Input::GetKeyRelease('1'))
	{
		Manager::SetScene<GameClear>();
	}
	if (Input::GetKeyRelease('2'))
	{
		Manager::SetScene<GameOver>();
	}

#endif



	////カメラが存在しない場合はソートしない
	//if (transformPtr != nullptr) {

	//	TransForm& cameratransform = *transformPtr;

	//	//奥行きに応じてソート
	//	_GameObjects.sort([cameratransform](GameObject* a, GameObject* b) {
	//		bool a_actor = a->_DrowOrder;
	//		bool b_actor = b->_DrowOrder;

	//		//Actorのみ奥行きソートをする
	//		if (a_actor && b_actor) {
	//			return a->GetComponent<TransForm>()->CameraDistance(cameratransform) < b->GetComponent<TransForm>()->CameraDistance(cameratransform);
	//		}
	//		else if (a_actor) {

	//			return true;
	//		}
	//		else if (b_actor) {

	//			return false;
	//		}
	//		else {
	//			return false;
	//		}

	//		});
	//}

	////レイヤーでの並び替え
	//_GameObjects.sort([](GameObject* a, GameObject* b) {
	//	return a->_DrowOrder < b->_DrowOrder;
	//	});
	for (int i = 0; i < Draw_Max; i++)
	{
		//Updateの最後に消す
		_GameObjects[i].remove_if([](GameObject* object) {
			return object->Destroy();
			});
	}
}
