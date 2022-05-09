
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
	GameObjectRegistry::sInstance->RegisterCreationFunction('ENEM', EnemyServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAT', PlatformServer::StaticCreate);

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
	sf::Time m_enemy_spawn_countdown;
}


int Server::Run()
{
	srand(time(NULL));

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

	void CreateRandomPickup()
	{
		Vector3 pickupMin(0.f, 0.f, 0.f);
		Vector3 pickupMax(0.f, 720.f, 0.f);
		Vector3 pickupVelocity;
		sf::Int8 randomPosition;
		GameObjectPtr go;

		Vector3 pickupLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);

		randomPosition = rand() % 2 + 1;

		if (randomPosition == 1)
		{
			pickupLocation.mX = -20;
			pickupVelocity = Vector3(250.f, 0.f, 0);
		}
		else
		{
			pickupLocation.mX = 1290;
			pickupVelocity = Vector3(-250.f, 0.f, 0);
		}

		PickupPtr pickup = std::static_pointer_cast<Pickup>(GameObjectRegistry::sInstance->CreateGameObject('PICK'));
		
		pickup->SetLocation(pickupLocation);
		pickup->SetVelocity(pickupVelocity);
		
	}

	void CreateRandomEnemy()
	{
		sf::Int8 randomPosition;
		Vector3 enemyLocation;
		Vector3 enemyVelocity;

		randomPosition = rand() % 2 + 1;

		if(randomPosition == 1)
		{
			enemyLocation = Vector3(10, 685, 0);
			enemyVelocity = Vector3(250.f, 0.f, 0);
		}
		else
		{
			enemyLocation = Vector3(1270, 685, 0);
			enemyVelocity = Vector3(-250.f, 0.f, 0);
		}

		//go = GameObjectRegistry::sInstance->CreateGameObject('ENEM');
		EnemyPtr enemy = std::static_pointer_cast<Enemy>(GameObjectRegistry::sInstance->CreateGameObject('ENEM'));

		enemy->SetLocation(enemyLocation);
		enemy->SetVelocity(enemyVelocity);
	}
}


void Server::SetupWorld()
{
	GameObjectPtr platform1 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	GameObjectPtr platform2 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	GameObjectPtr platform3 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');

	//platform1 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	//platform2 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	//platform3 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');

	platform1->SetLocation(Vector3(980.f, 500.f, 0));
	platform2->SetLocation(Vector3(300.f, 500.f, 0));
	platform3->SetLocation(Vector3(640.f, 300.f, 0));
	//spawn some random mice
	//CreateRandomMice(10);

	//spawn more random mice!
	//CreateRandomMice(10);
}

void Server::DoFrame()
{
	tick_time += tick_clock.getElapsedTime();
	m_pickup_spawn_countdown += tick_time;
	m_enemy_spawn_countdown += tick_time;

	if (m_pickup_spawn_countdown >= sf::seconds(100000.f))
	{
		tick_clock.restart();
		m_pickup_spawn_countdown = sf::seconds(0.f);
		CreateRandomPickup();
	}
	
	if (m_enemy_spawn_countdown >= sf::seconds(500000.f))
	{
		tick_clock.restart();
		m_enemy_spawn_countdown = sf::seconds(0.f);
		CreateRandomEnemy();
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
