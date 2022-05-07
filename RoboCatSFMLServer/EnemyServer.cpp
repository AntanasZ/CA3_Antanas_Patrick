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


bool EnemyServer::HandleCollisionWithCat(RoboCat* inCat)
{
	//kill yourself!
	//SetDoesWantToDie(true);

	//ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);

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