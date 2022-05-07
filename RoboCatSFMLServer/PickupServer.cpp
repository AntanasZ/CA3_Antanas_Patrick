#include "RoboCatServerPCH.hpp"


PickupServer::PickupServer()
{
	//pickup lives 4 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 4.f;
}

void PickupServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool PickupServer::HandleCollisionWithCat(RoboCat* inCat)
{
	//kill yourself!
	SetDoesWantToDie(true);

	ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);

	return false;
}

void PickupServer::Update()
{
	Pickup::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}