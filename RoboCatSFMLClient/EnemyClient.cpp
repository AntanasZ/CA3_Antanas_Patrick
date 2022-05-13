#include "RoboCatClientPCH.hpp"

EnemyClient::EnemyClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("orca"));
}

