#include "RoboCatClientPCH.hpp"

EnemyClient::EnemyClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));

	//mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("tomato"));

	sf::Int8 randomEnemy = rand() % 3 + 1;

	switch (randomEnemy)
	{
	case 1:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("diver"));
		break;
	case 2:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("octopus"));
		break;
	case 3:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("orca"));
		break;
	}
}

