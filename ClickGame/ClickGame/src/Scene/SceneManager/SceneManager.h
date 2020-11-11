/**
* @file SceneManager.h
* @brief シーン管理クラスを宣言したファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "Scene.h"
#include "SceneChanger.h"
#include "..//..//Utility/Singleton.h"
#include <stack>
#include <memory>

class SceneManager : public SceneChanger
{
	friend Singleton<SceneManager>;
public:
	/**
	* @biref コンストラクタ
	*/
	SceneManager();

	/**
	* @brief デストラクタ
	*/
	~SceneManager();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @biref 描画関数
	*/
	void Draw();

	/**
	* @biref シーン変更関数
	*/
	void ChangeScene(SceneID id) override;

	/**
	* @biref シーン追加関数
	*/
	void PushScene(SceneID id) override;

	/**
	* @biref シーン削除関数
	*/
	void PopScene() override;

	/**
	* @biref ゲーム終了関数
	*/
	void QuitGame() override;

private:
	std::stack<std::shared_ptr<Scene>> SceneStack;		//!< シーン保持変数
};

#define THE_SCENEMANAGER SingletonSceneManager::GetInstance()

#endif // !SCENEMANAGER_H_