/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatClientPCH.hpp"

DiverClient::DiverClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("diver"), false);
}

