#include "GameScene.h"

#include "..//..//Engine/Input/InputManager.h"
#include <thread>

GameScene::GameScene(SceneChanger* scene_changer) : Scene(sceneChanger)
{
	ThreadHandle = CreateThread(
		nullptr,                    // �Z�L�����e�B����
		0,                          // �X�^�b�N�T�C�Y
		this->LoadResources,        // �X���b�h�֐�
		nullptr,                    // �X���b�h�֐��ɓn������
		0,                          // �쐬�I�v�V����
		&ThreadID);             // �X���b�hID

	CurrentState = SceneState::Load;
}

GameScene::~GameScene()
{
}

void GameScene::Load()
{
	if (WaitForSingleObject(ThreadHandle, 0) == WAIT_OBJECT_0)
	{
		CurrentState = SceneState::Main;
	}
}

DWORD WINAPI GameScene::LoadResources(LPVOID lpParam)
{
	return 0;
}

void GameScene::Main()
{

}

void GameScene::Update()
{
	switch (CurrentState)
	{
	case SceneState::Load:
		Load();
		break;
	case SceneState::Main:
		Main();
		break;
	default:
		break;
	}
}

void GameScene::Draw()
{

}