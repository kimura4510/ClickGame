/**
* @file Scene.h
* @brief シーンの基底クラスを宣言したファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef SCENE_H_
#define SCENE_H_

#include <Windows.h>
#include "SceneDefinition.h"
#include "SceneChanger.h"

class Scene
{
public:
	/**
	* @biref コンストラクタ
	* @param[in] sceneChanger_ シーン変更のためのインターフェイス(SceneManager)のポインタ
	*/
	Scene(SceneChanger* scene_changer) :
		SceneChanger(scene_changer),
		CurrentState(SceneState::Init),
		ThreadHandle(nullptr),
		ThreadID(0)
	{	}

	/**
	* @biref デストラクタ
	*/
	virtual ~Scene() {	}

	/**
	* @biref 更新関数
	*/
	virtual void Update() = 0;

	/**
	* @biref 描画関数
	*/
	virtual void Draw() {	};
	
protected:

	/**
	* @biref Main処理関数
	*/
	virtual void Main() = 0;

	/**
	* @brief Loading処理関数
	*/
	virtual void Load() = 0;

protected:
	SceneChanger* SceneChanger;		//!< シーン変更のためのインターフェイスを保持するポインタ
	SceneState CurrentState;			//!< 現在のシーンの状態
	HANDLE ThreadHandle;				//!< マルチスレッド用のハンドル保存変数
	DWORD ThreadID;					//!< マルチスレッド用のスレッドID
};

#endif // !SCENE_H_