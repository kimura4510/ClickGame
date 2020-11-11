#include "TitleScene.h"

#include "..//..//Engine/Input/InputManager.h"
#include <thread>

#include <sstream>

TitleScene::TitleScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
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

TitleScene::~TitleScene()
{
}

void TitleScene::Load()
{
	if (WaitForSingleObject(ThreadHandle, 0) == WAIT_OBJECT_0)
	{
		CurrentState = SceneState::Main;
	}
}

DWORD WINAPI TitleScene::LoadResources(LPVOID lpParam_)
{
	return 0;
}


void TitleScene::Main()
{
}

void TitleScene::Update()
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

void TitleScene::Draw()
{
}