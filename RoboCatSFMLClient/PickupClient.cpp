#include "RoboCatClientPCH.hpp"

PickupClient::PickupClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish1"));
}