#include "GraphicManager.h"

#include <d3d9.h>
#include <d3dx9.h>

bool GraphicManager::InitGraphics(HWND hwindow)
{
	D3DPRESENT_PARAMETERS pres_param;

	Interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (Interface == nullptr)
	{
		return false;
	}

	ZeroMemory(&pres_param, sizeof(D3DPRESENT_PARAMETERS));

	pres_param.BackBufferCount = 1;
	pres_param.BackBufferFormat = D3DFMT_A8R8G8B8;
	pres_param.Windowed = false;
	pres_param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pres_param.BackBufferHeight = 1080;
	pres_param.BackBufferWidth = 1920;

	if (FAILED(Interface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&pres_param,
		&Device)))
	{
		return false;
	}

	D3DVIEWPORT9 ViewPort;

	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = pres_param.BackBufferWidth;
	ViewPort.Height = pres_param.BackBufferHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;

	if (FAILED(Device->SetViewport(&ViewPort)))
	{
		return false;
	}

	return true;
}

void GraphicManager::ReleaseGraphics()
{
	Device->Release();
	Interface->Release();
}

bool GraphicManager::DrawStart()
{
	Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);

	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (D3D_OK == Device->BeginScene())
	{
		return true;
	}

	return false;
}

void GraphicManager::DrawEnd()
{
	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}

void GraphicManager::DrawTexture(float x, float y, Texture* texture_data)
{
	CustomVertex TriStr[] =
	{
		{x, y, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f}, //left-top
		{x + texture_data->m_Width, y, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0.0f}, //right-top
		{x, y + texture_data->m_Height, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 1.0f},//left-bottom
		{x + texture_data->m_Width, y + texture_data->m_Height, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 1.0f},//right-bottom
	};

	//’¸“_\‘¢‚ÌŽw’è
	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	Device->SetTexture(0, texture_data->m_TextureData);
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		2,
		TriStr,
		sizeof(CustomVertex));
}

bool GraphicManager::CreateTexture(const char* file_name, Texture* texture_data)
{
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFileA(file_name, &info);

	if (FAILED(D3DXCreateTextureFromFileExA(Device,
		file_name,
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_data->m_TextureData)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC desc;

		if (FAILED(texture_data->m_TextureData->GetLevelDesc(0, &desc)))
		{
			texture_data->m_TextureData->Release();
			texture_data->m_TextureData = NULL;
			return false;
		}
		texture_data->m_Width = (float)desc.Width;
		texture_data->m_Height = (float)desc.Height;
	}
	return true;
}