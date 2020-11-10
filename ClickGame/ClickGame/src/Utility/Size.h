/**
* @file Size.h
* @brief �f�[�^�̃T�C�Y(�c�A��)��ۑ��ł���\���̂̐錾
* @author �ؑ��N��
* @data 2020/11/11
*/
#ifndef SIZE_H_
#define SIZE_H_

struct Size
{
	//Constructor
	Size()
	{
		Width = 0.0f;
		Height = 0.0f;
	}

	/**
	* @brief Constructor
	* @param[in] width ����
	* @param[in] height �c��
	*/
	Size(float width, float height)
	{
		Width = width;
		Height = height;
	}

	/**
	* @brief Constructor
	* @param[in] size �R�s�[�p�T�C�Y�f�[�^
	*/
	Size(const Size& size)
	{
		this->Width = size.Width;
		this->Height = size.Height;
	}

	float Width;
	float Height;
};

#endif