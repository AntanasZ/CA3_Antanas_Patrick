#include "RoboCatServerPCH.hpp"


ProjectileServer::ProjectileServer()
{
	//projectile lives a second...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.f;
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

bool ProjectileServer::HandleCollisionWithCat(RoboCat* inCat)
{
	if (inCat->GetPlayerId() != GetPlayerId())
	{
		//kill yourself!
		SetDoesWantToDie(true);

		static_cast<RoboCatServer*>(inCat)->TakeDamage(GetPlayerId());

	}

	return false;
}


