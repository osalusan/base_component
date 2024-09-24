#pragma once
#include <list>
#include "main.h"
#include "renderer.h"

typedef enum{
	Draw_Camera =0,
	Draw_SkyDome,
	Draw_Filed,
	Draw_Actor,
	Draw_Effect,
	Draw_BillBoard,
	Draw_Polygon2D,
	Draw_Max

}DRAW_ORDER;

class GameObject;
class Player;
class Scene {
protected:
	std::list<GameObject*> _GameObjects[Draw_Max];
	Player* _player;
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual ~Scene() {};

	//特定のGameObjectの取得
	template <typename T>
	T* GetGameObject()//テンプレートはコンパイルしないとエラーが見えない
	{
		for (int i = 0; i < Draw_Max; i++)
		{
			for (GameObject* object : _GameObjects[i])
			{
				//キャスト
				//dynamic_cast->もし変換できなかった時にretにNULLが入る
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)
					return ret;
			}
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*>objectList;

		for (int i = 0; i < Draw_Max; i++)
		{
			for (GameObject* object : _GameObjects[i])
			{
				//キャスト
				//dynamic_cast->もし変換できなかった時にretにNULLが入る
				T* ret = dynamic_cast<T*>(object);

				if (ret != nullptr)
					objectList.push_back(ret);
			}
		}

		return objectList;
	}

	std::list<GameObject*> GetActorObjects() {return  _GameObjects[Draw_Actor];}

	template <typename T>//テンプレート関数
	T* AddGameObject(int Layer)
	{
		T* Gameobject = new T;
		//Gameobject->Init();
		_GameObjects[Layer].push_back(Gameobject);

		return Gameobject;
	}

	//Updateなどの途中から追加する時はこっち
	template <typename T>//テンプレート関数
	T* AddGameObject_T(int Layer)
	{
		T* Gameobject = new T;
		Gameobject->Init();
		_GameObjects[Layer].push_back(Gameobject);

		return Gameobject;
	}

	void AddGameObj_OtherPlayer(GameObject *obj,int Layer)
	{
		_GameObjects[Layer].push_back(obj);
	}

	Player * GetPlayerCharcter();
};