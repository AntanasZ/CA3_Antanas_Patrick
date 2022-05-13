#include "RoboCatServerPCH.hpp"


PickupServer::PickupServer()
{
	//pickup lives 5.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.5f;
}

void PickupServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool PickupServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	SetDoesWantToDie(true);

	ScoreBoardManager::sInstance->IncScore(inPlayer->GetPlayerId(), 1);

	//Make the shark grow 1% bigger
	inPlayer->SetScale(inPlayer->GetScale() * 1.01f);

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