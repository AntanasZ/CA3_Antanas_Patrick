#include "RoboCatClientPCH.hpp"

PickupClient::PickupClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	sf::Int8 randomSprite = rand() % 6 + 1;

	switch (randomSprite)
	{
	case 1:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish1"));
		break;
	case 2:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish2"));
		break;
	case 3:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish3"));
		break;
	case 4:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish4"));
		break;
	case 5:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish5"));
		break;
	case 6:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("fish6"));
		break;
	}
}