/**
* @file Size.h
* @brief データのサイズ(縦、横)を保存できる構造体の宣言
* @author 木村哲也
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
	* @param[in] width 横幅
	* @param[in] height 縦幅
	*/
	Size(float width, float height)
	{
		Width = width;
		Height = height;
	}

	/**
	* @brief Constructor
	* @param[in] size コピー用サイズデータ
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