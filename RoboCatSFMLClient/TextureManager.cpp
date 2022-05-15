/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatClientPCH.hpp"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	CacheTexture("background", "../Assets/Background.png");
	CacheTexture("rock", "../Assets/Rock.png");
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
	CacheTexture("boat", "../Assets/Boat.png");
	CacheTexture("mine", "../Assets/Mine.png");
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
