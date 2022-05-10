#include "RoboCatServerPCH.hpp"


BoatServer::BoatServer()
{
	//enemy lives 4 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.5f;
	mTimeBetweenShots = 0.8f;
}

void BoatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool BoatServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	//SetDoesWantToDie(true);

	//ScoreBoardManager::sInstance->IncScore(inPlayer->GetPlayerId(), 1);

	return false;
}

void BoatServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		ProjectilePtr projectile = std::static_pointer_cast<Projectile>(GameObjectRegistry::sInstance->CreateGameObject('PROJ'));
		projectile->InitFromBoat(this);
	}
}

void BoatServer::Update()
{
	Boat::Update();

	HandleShooting();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}