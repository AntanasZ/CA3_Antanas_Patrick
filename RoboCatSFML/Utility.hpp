#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
	class Sprite;
	class Text;
}

class Utility
{
public:
	static void CentreOrigin(sf::Sprite& sprite);
	static void CentreOrigin(sf::Text& text);
};

