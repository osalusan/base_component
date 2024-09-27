
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
#include "firepillar.h"
#include "billboard.h"
#include "input.h"
#include "gameover.h"
#include "gameclear.h"
#include "meshfiled.h"
#include "tree.h"
#include "grass.h"
#include "rock.h"
void Game::Init()
{

	AddGameObject<Player_Camera>(Draw_Camera)->m_TransForm->m_Rotation = { 0.0f,0.0f,0.0f };
	AddGameObject<Game_SkyDome>(Draw_SkyDome);
	AddGameObject<Player>(Draw_Actor)->m_TransForm->m_Position = {0.0f,0.0f,-40.0f};
	AddGameObject<MeshFiled>(Draw_Filed);
	auto filed = GetGameObject<MeshFiled>();
	for (int i = 0; i < 100; i++)
	{
		auto tree = AddGameObject<Tree>(Drawm_BillBoard);
		XMFLOAT2 pos = { (float)(rand() % 200 - 100),(float)(rand() % 200 - 100) };
		tree->m_TransForm->m_Position = { pos.x,0.0f,pos.y };
		
	}
	for (int i = 0; i < 30; i++)
	{
		auto rock = AddGameObject<Rock>(Draw_Actor);
		XMFLOAT2 pos = { (float)(rand() % 200 - 100),(float)(rand() % 200 - 100) };
		rock->m_TransForm->m_Position = { pos.x,0.0f,pos.y };
		rock->m_TransForm->m_Rotation = { (float)(rand() % 200 - 100) * 0.01f,(float)(rand() % 200 - 100) * 0.01f,0.0f };
	}
	//AddGameObject<BlueFire_Ring>(Draw_Effect)->m_TransForm->m_Position = { 0.0f,0.0f,15.0f };
	//AddGameObject<BillBoard>(Drawm_BillBoard)->SetBillBoard(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 0.0f));
	
	//AddGameObj(new UI(XMFLOAT3(0.0f, 0.0f, 0.0f)));
	Scene::Init();
}

void Game::Update()
{
	Scene::Update();
	if (m_Count == 0)
	{
		auto filed = GetGameObject<MeshFiled>();
		for (auto tree : Manager::GetScene()->GetGameObjects<Tree>())
		{
			tree->m_TransForm->m_Position.y = filed->GetHeight(tree->m_TransForm->m_Position);
		}
	}
	if (m_Count == 1)
	{
		auto filed = GetGameObject<MeshFiled>();
		for (auto rock : Manager::GetScene()->GetGameObjects<Rock>())
		{
			rock->m_TransForm->m_Position.y = filed->GetHeight(rock->m_TransForm->m_Position);
		}
	}
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
