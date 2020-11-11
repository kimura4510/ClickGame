/**
* @file SceneDefinition.h
* @brief シーン全体で使用するenum classを宣言したファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef SCENEDEFINITION_H_
#define SCENEDEFINITION_H_

enum class SceneID
{
	Tilte,
	Game,

	MaxSceneID,
};

enum class SceneState
{
	Init,
	Load,
	Main,
	End,
};

#endif // !SCENEDEFINITION_H_