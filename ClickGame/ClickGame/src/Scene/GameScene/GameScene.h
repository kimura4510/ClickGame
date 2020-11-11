/**
* @file GameScene.h
* @brief �Q�[���̖{�ҏ����t�@�C��
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "..//SceneManager/Scene.h"
#include "..//SceneManager/SceneChanger.h"

class GameScene : public Scene
{
public:
	GameScene(SceneChanger* scene_changer);
	virtual ~GameScene();

	void Update() override;
	void Draw() override;

private:
	static DWORD WINAPI LoadResources(LPVOID param);
	void Main() override;
	void Load() override;
};

#endif // !GAMESCENE_H_
