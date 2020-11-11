/**
* @file SceneManager.h
* @brief �V�[���Ǘ��N���X��錾�����t�@�C��
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "Scene.h"
#include "SceneChanger.h"
#include "..//..//Utility/Singleton.h"
#include <stack>
#include <memory>

class SceneManager : public SceneChanger
{
	friend Singleton<SceneManager>;
public:
	/**
	* @biref �R���X�g���N�^
	*/
	SceneManager();

	/**
	* @brief �f�X�g���N�^
	*/
	~SceneManager();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @biref �`��֐�
	*/
	void Draw();

	/**
	* @biref �V�[���ύX�֐�
	*/
	void ChangeScene(SceneID id) override;

	/**
	* @biref �V�[���ǉ��֐�
	*/
	void PushScene(SceneID id) override;

	/**
	* @biref �V�[���폜�֐�
	*/
	void PopScene() override;

	/**
	* @biref �Q�[���I���֐�
	*/
	void QuitGame() override;

private:
	std::stack<std::shared_ptr<Scene>> SceneStack;		//!< �V�[���ێ��ϐ�
};

#define THE_SCENEMANAGER SingletonSceneManager::GetInstance()

#endif // !SCENEMANAGER_H_