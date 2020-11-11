#include "GameScene.h"

#include "..//..//Engine/Input/InputManager.h"
#include <thread>

GameScene::GameScene(SceneChanger* sceneChanger) : Scene(sceneChanger)
{
	ThreadHandle = CreateThread(
		nullptr,                    // セキュリティ属性
		0,                          // スタックサイズ
		this->LoadResources,        // スレッド関数
		nullptr,                    // スレッド関数に渡す引数
		0,                          // 作成オプション
		&dwThreadID);             // スレッドID

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