
#include "RoboCatServerPCH.hpp"
#include <iostream>



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	s_instance.reset(new Server());

	return true;
}

Server::Server()
{

	GameObjectRegistry::sInstance->RegisterCreationFunction('RCAT', RoboCatServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PICK', PickupServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PROJ', ProjectileServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ENEM', ProjectileServer::StaticCreate);

	InitNetworkManager();

	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg(2);
	if (!latencyString.empty())
	{
		latency = stof(latencyString);
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);

	//sf::Time tick_rate = sf::seconds(1.f / 1.f);
	sf::Time tick_rate = sf::seconds(5.f);
	sf::Time tick_time = sf::Time::Zero;
	sf::Clock tick_clock;
	sf::Time m_pickup_spawn_countdown;
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}


namespace
{

	void CreateRandomPickups(int inPickupCount)
	{
		Vector3 pickupMin(10.f, -20.f, 0.f);
		Vector3 pickupMax(1270.f, -20.f, 0.f);
		GameObjectPtr go;

		for (int i = 0; i < inPickupCount; ++i)
		{
			go = GameObjectRegistry::sInstance->CreateGameObject('PICK');
			Vector3 pickupLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);
			go->SetLocation(pickupLocation);
		}
	}


}


void Server::SetupWorld()
{
	//spawn some random mice
	//CreateRandomMice(10);

	//spawn more random mice!
	//CreateRandomMice(10);
}

void Server::DoFrame()
{
	tick_time += tick_clock.getElapsedTime();
	m_pickup_spawn_countdown += tick_time;

	if (m_pickup_spawn_countdown >= sf::seconds(100000.f))
	{
		tick_clock.restart();
		m_pickup_spawn_countdown = sf::seconds(0.f);
		CreateRandomPickups(1);
	}
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnCats();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}

void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{

	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnCatForPlayer(playerId);
}

void Server::SpawnCatForPlayer(int inPlayerId)
{
	RoboCatPtr cat = std::static_pointer_cast<RoboCat>(GameObjectRegistry::sInstance->CreateGameObject('RCAT'));
	cat->SetColor(ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetColor());
	cat->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	cat->SetLocation(Vector3(600.f - static_cast<float>(inPlayerId), 400.f, 0.f));
}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	//kill client's cat
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	RoboCatPtr cat = GetCatForPlayer(playerId);
	if (cat)
	{
		cat->SetDoesWantToDie(true);
	}
}

RoboCatPtr Server::GetCatForPlayer(int inPlayerId)
{
	//run through the objects till we find the cat...
	//it would be nice if we kept a pointer to the cat on the clientproxy
	//but then we'd have to clean it up when the cat died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		RoboCat* cat = go->GetAsCat();
		if (cat && cat->GetPlayerId() == inPlayerId)
		{
			return std::static_pointer_cast<RoboCat>(go);
		}
	}

	return nullptr;

}
