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

	D3DVIEWPORT9 view_port;

	view_port.X = 0;
	view_port.Y = 0;
	view_port.Width = pres_param.BackBufferWidth;
	view_port.Height = pres_param.BackBufferHeight;
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	if (FAILED(Device->SetViewport(&view_port)))
	{
		return false;
	}

	D3DXCreateFont(Device, 20, 10, 0, 0, 0, 0, 0, 0, 0, "Times New Roman", &FontDevice);

	return true;
}

void GraphicManager::ReleaseGraphics()
{
	FontDevice->Release();
	Device->Release();
	Interface->Release();
}

bool GraphicManager::DrawStart()
{
	Device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);

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
	Device->Present(nullptr, nullptr, nullptr, nullptr);
}

void GraphicManager::DrawTexture(float x, float y, Texture* texture_data)
{
	CustomVertex TriStr[] =
	{
		{x, y, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f}, //left-top
		{x + texture_data->width, y, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0.0f}, //right-top
		{x, y + texture_data->height, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 1.0f},//left-bottom
		{x + texture_data->width, y + texture_data->height, 0.0f, 1.0f, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 1.0f},//right-bottom
	};

	//頂点構造の指定
	Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	Device->SetTexture(0, texture_data->textureData);
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		2,
		TriStr,
		sizeof(CustomVertex));
}

void GraphicManager::DrawFont(float x, float y, std::string string, FontColor color)
{
	RECT rect;
	rect.left = x;
	rect.right = x + 20;
	rect.top = y;
	rect.bottom = y + 20;
	FontDevice->DrawText(nullptr, string.c_str(), -1, &rect, 0, 0xFFFFFF);
}

bool GraphicManager::CreateTexture(std::string file_name, Texture* texture_data)
{
	D3DXIMAGE_INFO d3dx_image_info;

	D3DXGetImageInfoFromFileA(file_name.c_str(), &d3dx_image_info);

	if (FAILED(D3DXCreateTextureFromFileExA(Device,
		file_name.c_str(),
		d3dx_image_info.Width,
		d3dx_image_info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&texture_data->textureData)))
	{
		return false;
	}
	else
	{
		D3DSURFACE_DESC d3d_surface_desc;

		if (FAILED(texture_data->textureData->GetLevelDesc(0, &d3d_surface_desc)))
		{
			texture_data->textureData->Release();
			texture_data->textureData = NULL;
			return false;
		}
		texture_data->width = (float)d3d_surface_desc.Width;
		texture_data->height = (float)d3d_surface_desc.Height;
	}
	return true;
}