#include "RoboCatServerPCH.hpp"


DiverServer::DiverServer()
{
	//diver lives 6.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 6.5f;
}

void DiverServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool DiverServer::HandleCollisionWithPlayer(Player* inPlayer)
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

void DiverServer::Update()
{
	Diver::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}