#include "RoboCatClientPCH.hpp"

BoatClient::BoatClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("boat"), false);
}

