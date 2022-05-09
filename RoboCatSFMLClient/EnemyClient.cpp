#include "RoboCatClientPCH.hpp"

EnemyClient::EnemyClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("tomato"));

	/*sf::Int8 randomEnemy = rand() % 6 + 1;

	switch (randomEnemy)
	{
	case 1:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("creeper"));
		break;
	case 2:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("ghost"));
		break;
	case 3:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("pterodactyl"));
		break;
	case 4:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("skull"));
		break;
	case 5:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("turtle"));
		break;
	case 6:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("stripe"));
		break;
	}*/
}

