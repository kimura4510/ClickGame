/**
* @file Window.h
* @brief Window�����Ɋւ���t�@�C��
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

#include <string>

#define WINDOW_CLASS_NAME "Window" //�E�B���h�E�N���X��

class Window
{
public:
	/** �E�B���h�E���쐬����֐�@n
	* �����Ŏw�肳�ꂽ���e�ŃE�B���h�E���쐬���܂�
	* @return �쐬���ʁA�����̏ꍇ��true
	* @param[in] instance �C���X�^���X�n���h��
	* @param[in] width ����
	* @param[in] height �c��
	* @param[in] title �^�C�g���o�[�ɕ\������镶����
	*/
	HWND MakeWindow(HINSTANCE instance, int width, int height, std::string title);
};

#endif // !WINDOW_H_
