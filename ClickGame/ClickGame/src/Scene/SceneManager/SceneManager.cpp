#include "SceneManager.h"

#include "..//..//Engine/Graphic/GraphicManager.h"
#include "..//TitleScene/TitleScene.h"
#include "..//GameScene/GameScene.h"

SceneManager::SceneManager()
{
	SceneStack.push(std::make_shared<TitleScene>(this));
}

SceneManager::~SceneManager()
{
	while (!SceneStack.empty())
	{
		SceneStack.pop();
	}
}

void SceneManager::ChangeScene(SceneID id)
{
	while (!SceneStack.empty())
	{
		SceneStack.pop();
	}
	
	PushScene(id);
}

void SceneManager::PushScene(SceneID id)
{
	switch (id)
	{
	case SceneID::Tilte:
		SceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneID::Game:
		SceneStack.push(std::make_shared<GameScene>(this));
		break;
	case SceneID::MaxSceneID:
		break;
	default:
		break;
	}
}

void SceneManager::PopScene()
{
	if (SceneStack.size() > 1)
	{ 
		SceneStack.pop();
	}
}

void SceneManager::QuitGame()
{
}

void SceneManager::Update()
{
	SceneStack.top()->Update();
}

void SceneManager::Draw()
{
	THE_GRAPHIC.DrawStart();

	SceneStack.top()->Draw();

	THE_GRAPHIC.DrawEnd();
}