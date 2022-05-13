#include "RoboCatServerPCH.hpp"


EnemyServer::EnemyServer()
{
	//enemy lives 4 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.5f;
}

void EnemyServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool EnemyServer::HandleCollisionWithPlayer(Player* inPlayer)
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

void EnemyServer::Update()
{
	Enemy::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}