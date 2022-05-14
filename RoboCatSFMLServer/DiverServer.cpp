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
	
	/*if(!inPlayer->GetInvulnerable())
	{
		inPlayer->SetInvulnerable(true);
		static_cast<PlayerServer*>(inPlayer)->TakeDamage(inPlayer->GetPlayerId(), 1);
	}*/
	
	//Make the shark grow 3% bigger
	inPlayer->SetScale(inPlayer->GetScale() * 1.03f);
	inPlayer->SetCollisionRadius(inPlayer->GetCollisionRadius() * 1.03f);

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
		//projectile->SetScale(GetScale() * 0.5f);
		//projectile->SetCollisionRadius(10.f);
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