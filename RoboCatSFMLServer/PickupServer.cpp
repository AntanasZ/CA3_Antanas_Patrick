/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatServerPCH.hpp"


PickupServer::PickupServer()
{
	//pickup lives 5.5 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.5f;

	sf::Int8 randomSprite = rand() % 6 + 1;

	SetSpriteNumber(randomSprite);
}

void PickupServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool PickupServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	SetDoesWantToDie(true);

	ScoreBoardManager::sInstance->IncScore(inPlayer->GetPlayerId(), 5);

	//Make the shark grow 1% bigger
	inPlayer->SetScale(inPlayer->GetScale() * 1.01f);
	inPlayer->SetCollisionRadius(inPlayer->GetCollisionRadius() * 1.01f);
	
	//PLay collect pickup sound
	inPlayer->PlayCollectPickupSound();

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