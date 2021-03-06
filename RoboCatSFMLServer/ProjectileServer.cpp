/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
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

		if (!inPlayer->GetInvulnerable())
		{
			inPlayer->SetInvulnerable(true);
			static_cast<PlayerServer*>(inPlayer)->TakeDamage(inPlayer->GetPlayerId(), 1);

			//Play a sound
			inPlayer->PlayHitSound();
		}

	}

	return false;
}



