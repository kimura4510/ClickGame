#ifndef SCENE_H_
#define SCENE_H_

#include <Windows.h>
#include "SceneDefinition.h"
#include "SceneChanger.h"

class Scene
{
public:
	/**
	* @biref �R���X�g���N�^
	* @param[in] sceneChanger_ �V�[���ύX�̂��߂̃C���^�[�t�F�C�X(SceneManager)�̃|�C���^
	*/
	Scene(SceneChanger* sceneChanger_) :
		pSceneChanger(sceneChanger_),
		CurrentState(SceneState::Init),
		ThreadHandle(nullptr),
		dwThreadID(0)
	{	}

	/**
	* @biref �f�X�g���N�^
	*/
	virtual ~Scene() {	}

	/**
	* @biref �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @biref �`��֐�
	*/
	virtual void Draw() {	};
	
protected:

	/**
	* @biref Main�����֐�
	*/
	virtual void Main() = 0;

	/**
	* @brief Loading�����֐�
	*/
	virtual void Load() = 0;

protected:
	SceneChanger* pSceneChanger;		//!< �V�[���ύX�̂��߂̃C���^�[�t�F�C�X��ێ�����|�C���^
	SceneState CurrentState;			//!< ���݂̃V�[���̏��
	HANDLE ThreadHandle;				//!< �}���`�X���b�h�p�̃n���h���ۑ��ϐ�
	DWORD dwThreadID;					//!< �}���`�X���b�h�p�̃X���b�hID
};

#endif // !SCENE_H_