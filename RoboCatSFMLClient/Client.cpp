/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatClientPCH.hpp"

bool Client::StaticInit()
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();
	InputManager::StaticInit();

	WindowManager::StaticInit();
	FontManager::StaticInit();
	TextureManager::StaticInit();
	RenderManager::StaticInit();
	

	HUD::StaticInit();

	s_instance.reset(client);

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAY', PlayerClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PICK', PickupClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PROJ', ProjectileClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ORCA', OrcaClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('DIVE', DiverClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('OCTO', OctopusClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAT', PlatformClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ROCK', RockClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOAT', BoatClient::StaticCreate);

	string destination = StringUtils::GetCommandLineArg(1);
	string name = StringUtils::GetCommandLineArg(2);

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(destination);

	NetworkManagerClient::StaticInit(*serverAddress, name);

	//NetworkManagerClient::sInstance->SetSimulatedLatency(0.0f);

	mBackgroundMusic.openFromFile("../Assets/Music/GameTheme.wav");
	
	mBackgroundMusic.play();
	
	mBackgroundMusic.setLoop(true);
}



void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	RenderManager::sInstance->Render();

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent(sf::Event& p_event)
{
	switch (p_event.type)
	{
	case sf::Event::KeyPressed:
		InputManager::sInstance->HandleInput(EIA_Pressed, p_event.key.code);
		break;
	case sf::Event::KeyReleased:
		InputManager::sInstance->HandleInput(EIA_Released, p_event.key.code);
		break;
	default:
		break;
	}
}

bool Client::PollEvent(sf::Event& p_event)
{
	return WindowManager::sInstance->pollEvent(p_event);
}


