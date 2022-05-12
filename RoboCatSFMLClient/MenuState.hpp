#pragma once
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState
{
public:
	static void StaticInit();
	static std::unique_ptr<MenuState>		sInstance;
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

private:
	MenuState();
	SpriteComponentPtr m_background_sprite;
	GUI::Container m_gui_container;
};