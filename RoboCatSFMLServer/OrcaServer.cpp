#include "RoboCatServerPCH.hpp"


OrcaServer::OrcaServer()
{
	//orca lives 5.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.5f;
}

void OrcaServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool OrcaServer::HandleCollisionWithPlayer(Player* inPlayer)
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

void OrcaServer::Update()
{
	Orca::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}