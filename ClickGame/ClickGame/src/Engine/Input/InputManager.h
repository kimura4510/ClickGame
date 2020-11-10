/**
* @file Fraphic.h
* @biref ���͂Ɋւ���t�@�C��
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <dinput.h>
#include <XInput.h>
#include <vector>
#include "..//..//Utility/Singleton.h"

#define MAX_CONTROLLERS 4	//!< XInput�̎擾�\�ȍő�R���g���[���[��

enum class InputState
{
	Not_Push,
	Release,
	PushDown,
	Push,
};

enum class MouseButton
{
	Left,
	Right,
	Center,
	Max_Mouse_Btn
};

class InputManager
{

	friend Singleton<InputManager>;

public:
	/**
	* @brief Input�@�\�̏������֐�
	* �f�o�C�X�̓��͎擾�ɕK�v�ȏ��������s���܂�
	* @return ���������ʁA�����̏ꍇ��true
	* @param[in] hInstance_	�C���X�^���X�n���h��
	* @param[in] hWindow_	�E�B���h�E�n���h��
	*/
	bool Init(HINSTANCE hInstance_, HWND hWindow_);

	/**
	* @brief Input�@�\�̏I���֐�
	* Input�@�\���I�������܂�
	*/
	void Release();

	/**
	* @biref ���͏��̍X�V
	* �}�E�X�A�L�[�{�[�h�A�Q�[���p�b�h�̓��͏��̍X�V���s���܂�
	*/
	void Update();


	//!< �ȉ��}�E�X�֘A�̊֐�
		/***
		* @biref �}�E�X��������Ă��邩�̏��擾�֐�
		* @param[in] button_ �}�E�X�̃{�^���̎��
		*/
	bool GetMouse(MouseButton button_)const;

	/***
	* @biref �}�E�X�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �}�E�X�̃{�^���̎��
	*/
	bool GetMouseDown(MouseButton button_)const;

	/***
	* @biref �}�E�X�������ꂽ�u�Ԃ��̏��擾�֐�
	* @param[in] button_ �}�E�X�̃{�^���̎��
	*/
	bool GetMouseUp(MouseButton button_)const;

	/***
	* @biref �}�E�X���W�̎擾�֐�
	*/
	POINT GetMousePos()const;

private:
	/**
	* @brief �}�E�X�p�̃f�o�C�X�̐���
	* �}�E�X�p��DirectInputDevice�𐶐��A���������܂�
	* @return �������ʁA�����̏ꍇ��true
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief �}�E�X�̓��͏��X�V�֐�
	*/
	void UpdateMouseState();

	/**
* @biref �R���X�g���N�^
*/
	InputManager();

	/**
	* @biref �f�X�g���N�^
	*/
	~InputManager() { }

private:
	static LPDIRECTINPUT8 Interface;		//!< DirectInput8�̃C���^�[�t�F�C�X
	LPDIRECTINPUTDEVICE8 MouseDevice;		//!< �}�E�X�p�̃f�o�C�X

	InputState MouseState[3];		//!< �}�E�X���͏��
};

#define THE_INPUTMANAGER InputMA::GetInstance()

#endif INPUT_MANAGER