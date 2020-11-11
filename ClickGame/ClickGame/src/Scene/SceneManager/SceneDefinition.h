/**
* @file SceneDefinition.h
* @brief �V�[���S�̂Ŏg�p����enum class��錾�����t�@�C��
* @author �ؑ��N��
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