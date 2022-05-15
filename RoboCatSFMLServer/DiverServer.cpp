/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatServerPCH.hpp"


DiverServer::DiverServer()
{
	//diver lives 6.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 6.5f;

	mTimeBetweenShots = 2.f;
}

void DiverServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool DiverServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	SetDoesWantToDie(true);

	//Make the shark grow 3% bigger
	inPlayer->SetScale(inPlayer->GetScale() * 1.03f);
	inPlayer->SetCollisionRadius(inPlayer->GetCollisionRadius() * 1.03f);

	//Play a sound
	inPlayer->PlayCollectPickupSound();

	return false;
}

void DiverServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		ProjectilePtr projectile = std::static_pointer_cast<Projectile>(GameObjectRegistry::sInstance->CreateGameObject('PROJ'));
		projectile->InitFromDiver(this);
	}
}

void DiverServer::Update()
{
	Diver::Update();

	HandleShooting();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}