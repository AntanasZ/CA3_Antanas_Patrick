#include "RoboCatClientPCH.hpp"

PlayerSpriteComponent::PlayerSpriteComponent(GameObject* inGameObject) :
	SpriteComponent(inGameObject)
{}

sf::Sprite& PlayerSpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto sca = mGameObject->GetScale();

	m_sprite.setPosition(pos.mX, pos.mY);

	Player* player = dynamic_cast<Player*>(mGameObject);

	auto vel = player->GetVelocityLeftRight();
	Vector3 playerColor = player->GetColor();
	m_sprite.setColor(sf::Color(playerColor.mX, playerColor.mY, playerColor.mZ, 255));

	m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));

	if (!player->IsFacingRight() && m_sprite.getScale().x > 0)
	{
		//m_sprite.scale(-1.f, 1.f);
		m_sprite.setScale(sf::Vector2f(-1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
	}
	else if (player->IsFacingRight() && m_sprite.getScale().x < 0)
	{
		m_sprite.scale(-1.f, 1.f);
		m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
	}
	
	return m_sprite;
}
