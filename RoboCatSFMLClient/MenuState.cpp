#include "RoboCatClientPCH.hpp"
#include "MenuState.hpp"
#include "Button.hpp"

MenuState::MenuState()
{
	m_background_sprite->SetTexture(TextureManager::sInstance->GetTexture("background"));
	//WindowManager::sInstance->draw(sf::Sprite(*TextureManager::sInstance->GetTexture("background")));
	//WindowManager::sInstance->draw(sf::Sprite(*TextureManager::sInstance->GetTexture("background")));

	auto join_play_button = std::make_shared<GUI::Button>();
	join_play_button->setPosition(400, 275);
	join_play_button->SetText("Join");
	join_play_button->SetCallback([this]()
		{

		});

	auto exit_button = std::make_shared<GUI::Button>();
	exit_button->setPosition(400, 425);
	exit_button->SetText("Exit");
	exit_button->SetCallback([this]()
		{
		});

	m_gui_container.Pack(join_play_button);
	m_gui_container.Pack(exit_button);

	// Play menu theme
	//context.music->Play(MusicThemes::kMenuTheme);
}

void MenuState::Draw()
{
	//sf::RenderWindow& window = *GetContext().window;

    //WindowManager::sInstance->draw(sf::Sprite(*TextureManager::sInstance->GetTexture("background")));

	//window.setView(window.getDefaultView());
	WindowManager::sInstance->draw(m_background_sprite);
	WindowManager::sInstance->draw(m_gui_container);
}

bool MenuState::Update(sf::Time dt)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	m_gui_container.HandleEvent(event);
	return false;
}

