#include "RoboCatClientPCH.hpp"

OrcaClient::OrcaClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("orca"), false);
}

