/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatServerPCH.hpp"
#include <iostream>



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	s_instance.reset(new Server());

	return true;
}

Server::Server() :
	m_rock_spawn_countdown(0.f),
	m_pickup_spawn_countdown(0.f),
	m_enemy_spawn_countdown(0.f),
	m_boat_spawn_countdown(0.f),
	m_game_timer(180.f)
{

	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAY', PlayerServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PICK', PickupServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PROJ', ProjectileServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ORCA', OrcaServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('DIVE', DiverServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('OCTO', OctopusServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PLAT', PlatformServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('ROCK', RockServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('BOAT', BoatServer::StaticCreate);

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
	sf::Time m_boat_spawn_countdown;
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
		Vector3 pickupMin(0.f, 40.f, 0.f);
		Vector3 pickupMax(0.f, 700.f, 0.f);
		Vector3 pickupVelocity;
		sf::Int8 randomPosition;

		Vector3 pickupLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);

		randomPosition = rand() % 2 + 1;

		PickupPtr pickup = std::static_pointer_cast<Pickup>(GameObjectRegistry::sInstance->CreateGameObject('PICK'));
		
		if (randomPosition == 1)
		{
			pickupLocation.mX = -20;
			pickupVelocity = Vector3(250.f, 0.f, 0);
		}
		else
		{
			pickupLocation.mX = 1290;
			pickupVelocity = Vector3(-250.f, 0.f, 0);
			pickup->SetFacingRight(false);
		}

		pickup->SetLocation(pickupLocation);
		pickup->SetVelocity(pickupVelocity);		
	}

	void CreateRandomOrca()
	{
		Vector3 pickupMin(0.f, 40.f, 0.f);
		Vector3 pickupMax(0.f, 700.f, 0.f);
		sf::Int8 randomPosition;

		randomPosition = rand() % 2 + 1;

		Vector3 enemyLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);

		OrcaPtr orca = std::static_pointer_cast<Orca>(GameObjectRegistry::sInstance->CreateGameObject('ORCA'));
		Vector3 enemyVelocity = orca->GetVelocity();

		if (randomPosition == 1)
		{
			enemyLocation.mX = -20;
			enemyVelocity = Vector3(250.f, 0.f, 0);
		}
		else
		{
			enemyLocation.mX = 1290;
			orca->SetVelocity(Vector3(-1.f * enemyVelocity.mX, 0.f, 0.f));
			orca->SetFacingRight(false);
		}
		orca->SetLocation(enemyLocation);
	}

	void CreateRandomDiver()
	{
		Vector3 pickupMin(0.f, 40.f, 0.f);
		Vector3 pickupMax(0.f, 700.f, 0.f);
		sf::Int8 randomPosition;

		randomPosition = rand() % 2 + 1;

		Vector3 enemyLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);

		DiverPtr diver = std::static_pointer_cast<Diver>(GameObjectRegistry::sInstance->CreateGameObject('DIVE'));
		Vector3 enemyVelocity = diver->GetVelocity();

		if (randomPosition == 1)
		{
			enemyLocation.mX = -20;
			enemyVelocity = Vector3(250.f, 0.f, 0);
		}
		else
		{
			enemyLocation.mX = 1290;
			diver->SetVelocity(Vector3(-1.f * enemyVelocity.mX, 0.f, 0.f));
			diver->SetFacingRight(false);
		}

		diver->SetLocation(enemyLocation);
	}

	void CreateRandomOctopus()
	{
		Vector3 pickupMin(0.f, 40.f, 0.f);
		Vector3 pickupMax(0.f, 700.f, 0.f);
		sf::Int8 randomPosition;

		randomPosition = rand() % 2 + 1;

		Vector3 enemyLocation = RoboMath::GetRandomVector(pickupMin, pickupMax);

		OctopusPtr octopus = std::static_pointer_cast<Octopus>(GameObjectRegistry::sInstance->CreateGameObject('OCTO'));
		Vector3 enemyVelocity = octopus->GetVelocity();

		if (randomPosition == 1)
		{
			enemyLocation.mX = -20;
		}
		else
		{
			enemyLocation.mX = 1290;
			octopus->SetVelocity(Vector3(-1.f * enemyVelocity.mX, 0.f, 0.f));
			octopus->SetFacingRight(false);
		}
		octopus->SetLocation(enemyLocation);	}

	void CreateRandomRock()
	{
		Vector3 rockMin(10.f, -20.f, 0.f);
		Vector3 rockMax(1270.f, -20.f, 0.f);
		GameObjectPtr go;

		go = GameObjectRegistry::sInstance->CreateGameObject('ROCK');
		Vector3 pickupLocation = RoboMath::GetRandomVector(rockMin, rockMax);
		go->SetLocation(pickupLocation);
	}

	void CreateRandomBoat()
	{
		sf::Int8 randomPosition;
		Vector3 boatLocation = Vector3(0.f, -50.f, 0);
		Vector3 boatVelocity;

		randomPosition = rand() % 2 + 1;

		BoatPtr boat = std::static_pointer_cast<Boat>(GameObjectRegistry::sInstance->CreateGameObject('BOAT'));

		if (randomPosition == 1)
		{
			boatLocation.mX = -20;
			boatVelocity = Vector3(350.f, 0.f, 0);
		}
		else
		{
			boatLocation.mX = 1290;
			boatVelocity = Vector3(-350.f, 0.f, 0);
			boat->SetFacingRight(false);
		}

		boat->SetLocation(boatLocation);
		boat->SetVelocity(boatVelocity);
	}
}


void Server::SetupWorld()
{
	/*GameObjectPtr platform1 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	GameObjectPtr platform2 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	GameObjectPtr platform3 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');*/

	//platform1 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	//platform2 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');
	//platform3 = GameObjectRegistry::sInstance->CreateGameObject('PLAT');

	/*platform1->SetLocation(Vector3(980.f, 500.f, 0));
	platform2->SetLocation(Vector3(300.f, 500.f, 0));
	platform3->SetLocation(Vector3(640.f, 300.f, 0));*/
	//spawn some random mice
	//CreateRandomMice(10);

	//spawn more random mice!
	//CreateRandomMice(10);
}

void Server::DoFrame()
{
	/*tick_time += tick_clock.getElapsedTime();
	m_pickup_spawn_countdown += tick_time;
	m_enemy_spawn_countdown += tick_time;
	m_rock_spawn_countdown += tick_time;
	m_boat_spawn_countdown += tick_time;

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

	if (m_boat_spawn_countdown >= sf::seconds(1000000.f))
	{
		tick_clock.restart();
		m_boat_spawn_countdown = sf::seconds(0.f);
		CreateRandomBoat();
	}

	if(m_rock_spawn_countdown >= sf::seconds(200000.f))
	{
		tick_clock.restart();
		m_rock_spawn_countdown = sf::seconds(0.f);
		CreateRandomRock(1);
	}*/
	m_rock_spawn_countdown += Timing::sInstance.GetDeltaTime();
	m_enemy_spawn_countdown += Timing::sInstance.GetDeltaTime();
	m_pickup_spawn_countdown += Timing::sInstance.GetDeltaTime();
	m_boat_spawn_countdown += Timing::sInstance.GetDeltaTime();
	m_game_timer -= Timing::sInstance.GetDeltaTime();

	if (m_pickup_spawn_countdown >= 0.7f)
	{
		m_pickup_spawn_countdown = 0.f;
		CreateRandomPickup();
	}

	if (m_enemy_spawn_countdown >= 6.5f)
	{
		m_enemy_spawn_countdown = 0.f;
		
		sf::Int8 randomEnemy;
		randomEnemy = rand() % 3 + 1;

		if (randomEnemy == 1)
		{
			CreateRandomOrca();
		}
		else if (randomEnemy == 2)
		{
			CreateRandomDiver();
		}
		else
		{
			CreateRandomOctopus();
		}
	}

	if (m_rock_spawn_countdown >= 6.f)
	{
		m_rock_spawn_countdown = 0.f;
		CreateRandomRock();
	}

	if (m_boat_spawn_countdown >= 12.f)
	{
		m_boat_spawn_countdown = 0.f;
		CreateRandomBoat();
	}

	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnCats();

	Engine::DoFrame();
	
	NetworkManagerServer::sInstance->SendOutgoingPackets(m_game_timer);
}

void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{

	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnSharkForPlayer(playerId);
}

void Server::SpawnSharkForPlayer(int inPlayerId)
{
	PlayerPtr player = std::static_pointer_cast<Player>(GameObjectRegistry::sInstance->CreateGameObject('PLAY'));
	player->SetColor(ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetColor());
	player->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	player->SetLocation(Vector3(600.f - static_cast<float>(inPlayerId), 400.f, 0.f));
}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	//kill client's player
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	PlayerPtr player = GetSharkForPlayer(playerId);
	if (player)
	{
		player->SetDoesWantToDie(true);
	}
}

PlayerPtr Server::GetSharkForPlayer(int inPlayerId)
{
	//run through the objects till we find the player...
	//it would be nice if we kept a pointer to the player on the clientproxy
	//but then we'd have to clean it up when the player died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		Player* player = go->GetAsPlayer();
		if (player && player->GetPlayerId() == inPlayerId)
		{
			return std::static_pointer_cast<Player>(go);
		}
	}

	return nullptr;

}
