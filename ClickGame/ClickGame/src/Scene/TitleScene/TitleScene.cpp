#include "TitleScene.h"

#include "..//..//Engine/Input/InputManager.h"
#include <thread>

#include <sstream>

TitleScene::TitleScene(SceneChanger* sceneChanger_) : Scene(sceneChanger_)
{
	ThreadHandle = CreateThread(
		nullptr,                    // �Z�L�����e�B����
		0,                          // �X�^�b�N�T�C�Y
		this->LoadResources,        // �X���b�h�֐�
		nullptr,                    // �X���b�h�֐��ɓn������
		0,                          // �쐬�I�v�V����
		&dwThreadID);             // �X���b�hID

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