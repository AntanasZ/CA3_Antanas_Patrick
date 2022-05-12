#define _USE_MATH_DEFINES
#include "RoboCatPCH.hpp"
#include "Utility.hpp"

#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


#include <cmath>
#include <random>

namespace
{
	std::default_random_engine CreateRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = CreateRandomEngine();
}



//TODO should we just implement for base class - sf::Transformable?
void Utility::CentreOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void Utility::CentreOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

