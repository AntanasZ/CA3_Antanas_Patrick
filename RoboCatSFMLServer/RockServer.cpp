#include "RoboCatServerPCH.hpp"

RockServer::RockServer()
{
	//pickup lives 4 seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 4.f;
}

void RockServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool RockServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	//kill yourself!
	//SetDoesWantToDie(true);
	if (inPlayer->GetLocation().mX < GetLocation().mX)
	{
		inPlayer->SetLocation(Vector3(inPlayer->GetLocation().mX + GetCollisionRadius(), inPlayer->GetLocation().mY, inPlayer->GetLocation().mZ));
	}
	else if (inPlayer->GetLocation().mX > GetLocation().mX)
	{
		inPlayer->SetLocation(Vector3(inPlayer->GetLocation().mX - GetCollisionRadius(), inPlayer->GetLocation().mY, inPlayer->GetLocation().mZ));
	}

	if (inPlayer->GetLocation().mY < GetLocation().mY)
	{
		inPlayer->SetLocation(Vector3(inPlayer->GetLocation().mX, inPlayer->GetLocation().mY + GetCollisionRadius(), inPlayer->GetLocation().mZ));
	}
	else if (inPlayer->GetLocation().mY > GetLocation().mY)
	{
		inPlayer->SetLocation(Vector3(inPlayer->GetLocation().mX, inPlayer->GetLocation().mY - GetCollisionRadius(), inPlayer->GetLocation().mZ));
	}
	/*if(inCat->GetLocation().mX < GetLocation().mX || inCat->GetLocation().mX > GetLocation().mX)
	{
		inCat->SetVelocity(Vector3(0.f, inCat->GetVelocity().mY, inCat->GetVelocity().mZ));
	}

	if (inCat->GetLocation().mY < GetLocation().mY || inCat->GetLocation().mY > GetLocation().mY)
	{
		inCat->SetVelocity(Vector3(inCat->GetVelocity().mX,0.f, inCat->GetVelocity().mZ));
	}*/

	//ScoreBoardManager::sInstance->IncScore(inCat->GetPlayerId(), 1);

	return false;
}

void RockServer::Update()
{
	Rock::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}