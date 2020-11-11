#include "TitleScene.h"

#include <thread>

#include "..//..//Engine/Input/InputManager.h"
#include "..//..//Engine/Graphic/GraphicManager.h"


TitleScene::TitleScene(SceneChanger* scene_changer) : Scene(scene_changer)
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

DWORD WINAPI TitleScene::LoadResources(LPVOID param)
{
	return 0;
}

void TitleScene::Main()
{
	if (THE_INPUT.GetMouseDown(MouseButton::Left) == true)
	{
		SceneChanger->PushScene(SceneID::Game);
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
	std::string string = "Click to Start";
	THE_GRAPHIC.DrawFont(200, 160, string, FontColor::White);
}