#include "Texture.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	ReleaseAllTexture();
}

void TextureManager::ReleaseAllTexture()
{
	for (auto& texture : TextureList)
	{
		delete texture.second;
	}
	TextureList.clear();
}

bool TextureManager::ReleaseTexture(std::string key_name)
{
	if (HasKeyName(key_name) == false)
	{
		return false;
	}

	delete TextureList[key_name];
	TextureList.erase(key_name);
	return true;
}

bool TextureManager::LoadTexture(std::string file_name, std::string key_name)
{
	if (HasKeyName(key_name) == true)
	{
		return false;
	}

	TextureList[key_name.c_str()] = new Texture;
	return THE_GRAPHIC.CreateTexture(file_name, TextureList[key_name]);
}

Texture* TextureManager::GetTexture(std::string key_name)
{
	if (HasKeyName(key_name) == false)
	{
		return nullptr;
	}
	return TextureList[key_name];
}

bool TextureManager::HasKeyName(std::string key_name)
{
	auto it = TextureList.find(key_name);
	if (it == TextureList.end())
	{
		return false;
	}
	return true;
}