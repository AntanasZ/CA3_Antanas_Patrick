#include "RoboCatClientPCH.hpp"

PlatformClient::PlatformClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("platform"));
}

