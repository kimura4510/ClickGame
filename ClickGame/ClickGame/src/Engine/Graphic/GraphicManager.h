/**
* @file Fraphic.h
* @biref �`��ɕK�v�ȍ\���́A�N���X�Ȃǂ�錾�����t�@�C��
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>

#include "../../Utility/Singleton.h"

//!< @brief �e�N�X�`���f�[�^��T�C�Y��ێ�����\����
struct Texture
{
	LPDIRECT3DTEXTURE9 m_TextureData;	//!< �e�N�X�`���f�[�^
	float m_Width;						//!< ����
	float m_Height;						//!< �c��
};

//!< @brief 2D�`��p���_���W�ۑ��\����
struct CustomVertex
{
	float x;	//x���W
	float y;	//y���W
	float z;	//z���W
	float rhw;	//���Z��

	D3DCOLOR color;

	float tu;	//�e�N�X�`�����Wx
	float tv;	//�e�N�X�`�����Wy
};

enum class FontColor
{
	Black,
	Blue,
	Red,
	Green,
	White,
};

class GraphicManager
{
	friend Singleton<GraphicManager>;

public:
	/**
	* @brief Graphics�@�\�̏������֐�@n
	* �`��֘A���g�p�\�ɂ��邽�߂̏��������s���܂�@n
	* Engine.cpp��InitEngine�Ŏ��s���Ă���̂Ŏg�p�҂������Ŏg���K�v�͂���܂���
	* @param[in] window_handle �C���X�^���X�n���h��
	* @return ���������ʁA�����̏ꍇ��true
	*/
	bool InitGraphics(HWND window_handle);

	/**
	* @brief Graphics�@�\�̏I���֐�@n
	* �`��֘A�̏������I��������֐�@n
	* Engine.cpp��EndEngine�Ŏ��s���Ă���̂Ŏg�p�҂������Ŏg���K�v�͂���܂���
	*/
	void ReleaseGraphics();

	/**
	* @brief �`��J�n�֐�@n
	* �`��J�n��錾���A�o�b�N�o�b�t�@�̃N���A���s���܂�
	* @return �`��J�n�̐��ہA�����̏ꍇ��true
	*/
	bool DrawStart();

	/**
	* @brief �`��I���֐�@n
	* �`��̏I����錾���A�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ��܂�@n
	* ���̊֐��͕K��DrawStart�̌�Ɏ��s����悤�ɂ��Ă�������
	*/
	void DrawEnd();

	/**
	* @brief �e�N�X�`���쐬�֐�@n
	* �w�肳�ꂽ��񂩂�ǂݍ��݁A�e�N�X�`�����쐬���܂�
	* �J������Texture.h��LoadTexture���g�p���Ă�������
	* @return �쐬���ʁA�����̏ꍇ��true
	* @param[in] file_name �ǂݍ��ރe�N�X�`���̖��O(�p�X���܂�)
	* @param[out] texture_data �ǂݍ��܂ꂽ�e�N�X�`���𔽉f����f�[�^
	*/
	bool CreateTexture(std::string file_name, Texture* texture_data);

	/**
	* @brief �e�N�X�`���`��֐�@n
	* �w�肳�ꂽ�ʒu�Ƀe�N�X�`����`�悵�܂�@n
	* texture_data��Texture.h��GetTextureData���g�p���Ă�������
	* @param[in] x X���`����W
	* @param[in] y Y���`����W
	* @param[in] texture_data �`��Ŏg�p����e�N�X�`���̃f�[�^
	*/
	void DrawTexture(float x, float y, Texture* texture_data);

	/**
	* @brief �t�H���g�`��֐�@n
	* �w�肳�ꂽ�ʒu�ɕ�����`�悵�܂�@n
	* @param[in] x X���`����W
	* @param[in] y Y���`����W
	* @param[in] string �`�悷�镶��
	* @param[in] color �`�悷�镶���̐F
	*/
	void DrawFont(float x, float y, std::string string, FontColor color);

private:
	LPDIRECT3D9 Interface;			//!< DirectGraphics�C���^�[�t�F�[�X
	LPDIRECT3DDEVICE9 Device;		//!< DirectGraphics�f�o�C�X
	LPD3DXFONT FontDevice;				//!< DirectGraphics�̃t�H���g�̃f�o�C�X
};

#define THE_GRAPHIC Singleton<GraphicManager>::GetInstance()

#endif // !GRAPHICMANAGER_H_

