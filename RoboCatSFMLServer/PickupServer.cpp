#include "RoboCatServerPCH.hpp"


PickupServer::PickupServer()
{
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
}







