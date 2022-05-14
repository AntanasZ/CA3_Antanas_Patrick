#include "RoboCatClientPCH.hpp"


SpriteComponent::SpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	//and add yourself to the rendermanager...
	RenderManager::sInstance->AddComponent(this);
}

SpriteComponent::~SpriteComponent()
{
	//don't render me, I'm dead!
	RenderManager::sInstance->RemoveComponent(this);
}

void SpriteComponent::SetTexture(TexturePtr inTexture, bool resetting)
{
	auto tSize = inTexture->getSize();
	m_sprite.setTexture(*inTexture);
	m_sprite.setOrigin(tSize.x / 2, tSize.y / 2);

	if (!resetting)
	{
		m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
	}
}

void SpriteComponent::UpdateTexture()
{
	Pickup* pickup = mGameObject->GetAsPickup();

	mHasResetSprite = true;

	if (pickup)
	{
		switch (pickup->GetSpriteNumber())
		{
		case 1:
			SetTexture(TextureManager::sInstance->GetTexture("fish1"), true);
			break;
		case 2:
			SetTexture(TextureManager::sInstance->GetTexture("fish2"), true);
			break;
		case 3:
			SetTexture(TextureManager::sInstance->GetTexture("fish3"), true);
			break;
		case 4:
			SetTexture(TextureManager::sInstance->GetTexture("fish4"), true);
			break;
		case 5:
			SetTexture(TextureManager::sInstance->GetTexture("fish5"), true);
			break;
		case 6:
			SetTexture(TextureManager::sInstance->GetTexture("fish6"), true);
			break;
		}
	}
}

sf::Sprite& SpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto rot = mGameObject->GetRotation();
	auto sca = mGameObject->GetScale();
	m_sprite.setPosition(pos.mX, pos.mY);
	m_sprite.setRotation(rot);

	if (!mGameObject->IsFacingRight() && sca > 0)
	{
		m_sprite.scale(-1.f, 1.f);
		mGameObject->SetScale(sca * -1.f);
	}
	else if (mGameObject->IsFacingRight())
	{
		m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
	}

	if (!mHasResetSprite)
	{
		UpdateTexture();
	}

	return m_sprite;
}

