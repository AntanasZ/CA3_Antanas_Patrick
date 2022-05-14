#include "RoboCatClientPCH.hpp"

DiverClient::DiverClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("diver"), false);
}

