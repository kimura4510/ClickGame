/**
* @file Texture.h
* @brief �e�N�X�`���̓ǂݍ��݁A�J���ȂǁA�e�N�X�`���Ɋ֌W����֐��A�萔�̐錾
* @author �ؑ��N��
* @data 2020/11/11
*/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <unordered_map>

#include "..//Graphic/GraphicManager.h"

class TextureManager
{
public:
	/**
	* @brief �S�Ẵe�N�X�`���̉���֐�@n
	* �ǂݍ���ł���S�Ẵe�N�X�`����������܂�
	* ���̊֐���EndEngine�Ŏ��s���Ă�̂ŁA�J���������s����K�v�͂���܂���
	*/
	void ReleaseAllTexture();

	/**
	* @brief �w�肵���e�N�X�`���̊J���֐�
	* �w�肵���e�N�X�`�����J�����܂�
	* return ����ɐ��������ꍇ��true�A���s��false(�L�[�w��~�X)
	* param[in] key_name ����������e�N�X�`���̃L�[
	*/
	bool ReleaseTexture(std::string key_name);

	/**
	* @brief �e�N�X�`���ǂݍ��݊֐�
	* �w�肵���p�X�̃e�N�X�`����ǂݍ��݁Amap�ɓo�^���܂�
	* return �ǂݍ��݌��ʁA�����̏ꍇ��true
	* @param[in] file_name �ǂݍ��ރe�N�X�`���̃p�X���܂ޖ��O
	* @param[in] key_name �ǂݍ��ރe�N�X�`���ɓ��Ă͂߂�L�[
	*/
	bool LoadTexture(std::string file_name, std::string key_name);

	/**
	* @brief �e�N�X�`���f�[�^�̎擾�֐�
	* �w�肳�ꂽ���O�̃e�N�X�`���f�[�^���擾���܂�
	* @return �e�N�X�`���f�[�^�A���s�����ꍇ��nullptr
	* @param[in] file_name �擾�������e�N�X�`���̃L�[
	*/
	Texture* GetTexture(std::string file_name);

private:
	//�V���O���g��
//�R���X�g���N�^
	TextureManager();
	//�f�X�g���N�^
	~TextureManager();

	/**
	* @brief TextureList�̃L�[�`�F�b�N�֐�
	* �����Ŏw�肳�ꂽ�L�[���o�^����Ă��邩���m�F���܂�
	* return �o�^����Ă����ꍇ��true�A���o�^�̏ꍇ��false
	* @param[in] key_name�@�`�F�b�N�������L�[
	*/
	bool HasKeyName(std::string key_name);

private:
	//!< Texture�\���̕ۑ��p�|�C���^�z��
	std::unordered_map<std::string, Texture*> TextureList;
};


#endif // !TEXTURE_H_
