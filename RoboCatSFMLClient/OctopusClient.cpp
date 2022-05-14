#include "RoboCatClientPCH.hpp"

OctopusClient::OctopusClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("octopus"), false);
}

