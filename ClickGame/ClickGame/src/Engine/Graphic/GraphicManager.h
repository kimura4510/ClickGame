/**
* @file Fraphic.h
* @biref 描画に関するファイル
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include <Windows.h>
#include <d3d9.h>

#include "../../Utility/Singleton.h"

//!< @brief テクスチャデータやサイズを保持する構造体
struct Texture
{
	LPDIRECT3DTEXTURE9 m_TextureData;	//!< テクスチャデータ
	float m_Width;						//!< 横幅
	float m_Height;						//!< 縦幅
};

//!< @biref 3D描画用頂点座標保存構造体
struct CustomVertex3D
{
	float m_x;
	float m_y;
	float m_z;
	D3DCOLOR color;
	float tu, tv;
};

//!< @brief 2D描画用頂点座標保存構造体
struct CustomVertex
{
	float x;	//x座標
	float y;	//y座標
	float z;	//z座標
	float rhw;	//除算数

	D3DCOLOR color;

	float tu;	//テクスチャ座標x
	float tv;	//テクスチャ座標y
};

//!< @brief 3D描画のために必要なパラメータを設定するデータ構造体
struct DrawingData3D
{
	float m_x;	//x座標
	float m_y;	//y座標
	float m_z;	//z座標

	float m_tu;	//uテクスチャ座標
	float m_tv;	//vテクスチャ座標

	float m_width;	//幅
	float m_height;	//高さ

	DWORD m_color;	//color

	float m_rotx;	//x回転
	float m_roty;	//y回転
	float m_rotz;	//z回転

	float m_scalex;	//拡縮x
	float m_scaley;	//拡縮y
};

class GraphicManager
{
	friend Singleton<GraphicManager>;

public:
	/**
	* @brief Graphics機能の初期化関数@n
	* 描画関連を使用可能にするための初期化を行います@n
	* Engine.cppのInitEngineで実行しているので使用者が自分で使う必要はありません
	* @param[in] window_handle インスタンスハンドル
	* @return 初期化結果、成功の場合はtrue
	*/
	bool InitGraphics(HWND window_handle);

	/**
	* @brief Graphics機能の終了関数@n
	* 描画関連の処理を終了させる関数@n
	* Engine.cppのEndEngineで実行しているので使用者が自分で使う必要はありません
	*/
	void ReleaseGraphics();

	/**
	* @brief 描画開始関数@n
	* 描画開始を宣言し、バックバッファのクリアを行います
	* @return 描画開始の成否、成功の場合はtrue
	*/
	bool DrawStart();

	/**
	* @brief 描画終了関数@n
	* 描画の終了を宣言し、バックバッファとフロントバッファを入れ替えます@n
	* この関数は必ずDrawStartの後に実行するようにしてください
	*/
	void DrawEnd();

	/**
	* @brief テクスチャ作成関数@n
	* 指定された情報から読み込み、テクスチャを作成します
	* 開発側はTexture.hのLoadTextureを使用してください
	* @return 作成結果、成功の場合はtrue
	* @param[in] file_name 読み込むテクスチャの名前(パスを含む)
	* @param[out] texture_data 読み込まれたテクスチャを反映するデータ
	*/
	bool CreateTexture(const char* file_name, Texture* texture_data);

	/**
	* @brief テクスチャ描画関数@n
	* 指定された位置にテクスチャを描画します@n
	* texture_dataはTexture.hのGetTextureDataを使用してください
	* @param[in] x X軸描画座標
	* @param[in] y Y軸描画座標
	* @param[in] texture_data 描画で使用するテクスチャのデータ
	*/
	void DrawTexture(float x, float y, Texture* texture_data);

private:
	LPDIRECT3D9 Interface;		//DirectGraphicsインターフェース
	LPDIRECT3DDEVICE9 Device;		//DirectGraphicsデバイス
};

#endif // !GRAPHICMANAGER_H_

