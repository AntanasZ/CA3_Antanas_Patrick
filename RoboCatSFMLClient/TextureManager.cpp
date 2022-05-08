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
  CacheTexture("groundPlatform", "../Assets/GroundPlatform.png");
	CacheTexture("creeper", "../Assets/CreeperIdle.png");
	CacheTexture("ghost", "../Assets/GhostIdle.png");
	CacheTexture("pterodactyl", "../Assets/PterodactylIdle.png");
	CacheTexture("skull", "../Assets/SkullIdle.png");
	CacheTexture("stripe", "../Assets/StripeIdle.png");
	CacheTexture("turtle", "../Assets/TurtleIdle.png");
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
