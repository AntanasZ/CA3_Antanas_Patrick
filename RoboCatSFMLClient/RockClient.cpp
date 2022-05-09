#include "RoboCatClientPCH.hpp"

RockClient::RockClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("rock"));
}