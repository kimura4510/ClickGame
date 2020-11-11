/**
* @file SceneChanger.h
* @brief シーン変更機能を持つ抽象クラスを宣言したファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef SCENECHANGER_H_
#define SCENECHANGER_H_

#include "SceneDefinition.h"

class SceneChanger
{
public:
	/**
	* @biref コンストラクタ
	*/
	SceneChanger() = default;
	
	/**
	* @biref デストラクタ
	*/
	virtual ~SceneChanger() = default;
	
	/**
	* @biref シーン変更関数
	* スタックをクリアして指定したシーンを生成します
	* @param[in] scene_ 変更する次のシーン
	*/
	virtual void ChangeScene(SceneID id) = 0;

	/**
	* @biref シーン追加関数
	* スタックをクリアせずに指定したシーンを生成します
	* @param[in] scene_ 追加するシーン
	*/
	virtual void PushScene(SceneID id) = 0;

	/**
	* @biref シーン削除関数
	* 現在のシーンを削除します
	*/
	virtual void PopScene() = 0;

	/**
	* @biref ゲーム終了関数
	* ゲームを終了します
	*/
	virtual void QuitGame() = 0;
};

#endif // !SCENECHANGER_H_