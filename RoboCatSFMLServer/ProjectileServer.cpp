#include "RoboCatServerPCH.hpp"


ProjectileServer::ProjectileServer()
{
	//projectile lives 4.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 4.5f;
}

void ProjectileServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


void ProjectileServer::Update()
{
	Projectile::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}

}

bool ProjectileServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	if (inPlayer->GetPlayerId() != GetPlayerId())
	{
		//kill yourself!
		SetDoesWantToDie(true);

		static_cast<PlayerServer*>(inPlayer)->TakeDamage(GetPlayerId());

	}

	return false;
}



