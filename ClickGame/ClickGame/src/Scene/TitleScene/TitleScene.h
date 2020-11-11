/**
* @file TitleScene.h
* @biref �Q�[���N������ɕ\�������V�[���̏����t�@�C��
* @author �ؑ��N��
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
	TitleScene(SceneChanger* sceneChanger);
	virtual ~TitleScene();

	void Update() override;
	void Draw() override;

private:
	static DWORD WINAPI LoadResources(LPVOID lpParam);
	void Main() override;
	void Load() override;
};

#endif // !TITLESCENE_H_
