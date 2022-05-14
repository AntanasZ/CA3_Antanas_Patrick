#include "RoboCatServerPCH.hpp"


OctopusServer::OctopusServer()
{
	//octopus lives 7 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 7.f;
}

void OctopusServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool OctopusServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	//SetDoesWantToDie(true);
	
	if(!inPlayer->GetInvulnerable())
	{
		inPlayer->SetInvulnerable(true);
		static_cast<PlayerServer*>(inPlayer)->TakeDamage(inPlayer->GetPlayerId(), 1);
	}
	
	//ScoreBoardManager::sInstance->IncScore(inPlayer->GetPlayerId(), 1);

	return false;
}

void OctopusServer::Update()
{
	Octopus::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}