#include "RoboCatClientPCH.hpp"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	CacheTexture("cat", "../Assets/cat.png");
	CacheTexture("mouse", "../Assets/mouse.png");
	CacheTexture("tomato", "../Assets/Tomato.png");
	CacheTexture("yarn", "../Assets/yarn.png");
	CacheTexture("background", "../Assets/Background.png");
	CacheTexture("platform", "../Assets/Platform.png");
	CacheTexture("rock", "../Assets/Rock.png");
	CacheTexture("groundPlatform", "../Assets/GroundPlatform.png");
	CacheTexture("fish1", "../Assets/Fish1.png");
	CacheTexture("fish2", "../Assets/Fish2.png");
	CacheTexture("fish3", "../Assets/Fish3.png");
	CacheTexture("fish4", "../Assets/Fish4.png");
	CacheTexture("fish5", "../Assets/Fish5.png");
	CacheTexture("fish6", "../Assets/Fish6.png");
	CacheTexture("diver", "../Assets/Diver.png");
	CacheTexture("orca", "../Assets/Orca.png");
	CacheTexture("octopus", "../Assets/Octopus.png");
	CacheTexture("shark", "../Assets/Shark.png");
}

TexturePtr	TextureManager::GetTexture(const string& inTextureName)
{
	return mNameToTextureMap[inTextureName];
}

bool TextureManager::CacheTexture(string inTextureName, const char* inFileName)
{
	TexturePtr newTexture(new sf::Texture());
	if (!newTexture->loadFromFile(inFileName))
	{
		return false;
	}

	mNameToTextureMap[inTextureName] = newTexture;

	return true;

}
