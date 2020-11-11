#include "TitleScene.h"

#include <thread>

#include "..//..//Engine/Input/InputManager.h"
#include "..//..//Engine/Graphic/GraphicManager.h"


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
	if (THE_INPUT.GetMouseDown(MouseButton::Left) == true)
	{
		pSceneChanger->PushScene(SceneID::Game);
	}
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
	std::string str = "Click to Start";
	THE_GRAPHIC.DrawFont(200, 160, str, FontColor::White);
}