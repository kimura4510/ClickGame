﻿/**
* @file InputManager.h
* @brief 入力に必要な構造体やクラスを宣言したファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <dinput.h>
#include <vector>
#include "..//..//Utility/Singleton.h"

enum class InputState
{
	Not_Push,
	Release,
	Push_Down,
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
	* @brief Input機能の初期化関数
	* デバイスの入力取得に必要な初期化を行います
	* @return 初期化結果、成功の場合はtrue
	* @param[in] hInstance_	インスタンスハンドル
	* @param[in] hWindow_	ウィンドウハンドル
	*/
	bool Init(HINSTANCE instance, HWND window_handle);

	/**
	* @brief Input機能の終了関数
	* Input機能を終了させます
	*/
	void Release();

	/**
	* @biref 入力情報の更新
	* マウス、キーボード、ゲームパッドの入力情報の更新を行います
	*/
	void Update();


	//!< 以下マウス関連の関数
	
	/***
	* @biref マウスが押されているかの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouse(MouseButton button)const;

	/***
	* @biref マウスが押された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseDown(MouseButton button)const;

	/***
	* @biref マウスが離された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseUp(MouseButton button)const;

	/***
	* @biref マウス座標の取得関数
	*/
	POINT GetMousePos()const;

private:
	/**
	* @brief マウス用のデバイスの生成
	* マウス用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateMouseDevice(HWND window_handle);

	/**
	* @brief マウスの入力情報更新関数
	*/
	void UpdateMouseState();

	/**
* @biref コンストラクタ
*/
	InputManager();

	/**
	* @biref デストラクタ
	*/
	~InputManager() { }

private:
	static LPDIRECTINPUT8 Interface;		//!< DirectInput8のインターフェイス
	LPDIRECTINPUTDEVICE8 MouseDevice;		//!< マウス用のデバイス

	InputState MouseState[3];		//!< マウス入力情報
};

#define THE_INPUT Singleton<InputManager>::GetInstance()

#endif INPUTMANAGER_H_