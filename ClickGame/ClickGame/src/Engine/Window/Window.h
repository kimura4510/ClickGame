/**
* @file Window.h
* @brief Window生成に関するファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

#include <string>

#define WINDOW_CLASS_NAME "Window" //ウィンドウクラス名

class Window
{
public:
	/** ウィンドウを作成する関数@n
	* 引数で指定された内容でウィンドウを作成します
	* @return 作成結果、成功の場合はtrue
	* @param[in] instance インスタンスハンドル
	* @param[in] width 横幅
	* @param[in] height 縦幅
	* @param[in] title タイトルバーに表示される文字列
	*/
	HWND MakeWindow(HINSTANCE instance, int width, int height, std::string title);
};

#endif // !WINDOW_H_
