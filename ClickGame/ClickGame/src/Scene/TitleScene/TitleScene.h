/**
* @file TitleScene.h
* @brief ゲーム起動直後に表示されるシーンの処理ファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "..//SceneManager/Scene.h"
#include "..//SceneManager/SceneChanger.h"
#include "..//SceneManager/SceneDefinition.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneChanger* scene_changer);
	virtual ~TitleScene();

	void Update() override;
	void Draw() override;

private:
	static DWORD WINAPI LoadResources(LPVOID param);
	void Main() override;
	void Load() override;
};

#endif // !TITLESCENE_H_
