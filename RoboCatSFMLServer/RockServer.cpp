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


bool RockServer::HandleCollisionWithCat(RoboCat* inCat)
{
	//kill yourself!
	//SetDoesWantToDie(true);
	if (inCat->GetLocation().mX < GetLocation().mX)
	{
		inCat->SetLocation(Vector3(inCat->GetLocation().mX + GetCollisionRadius(), inCat->GetLocation().mY, inCat->GetLocation().mZ));
	}
	else if (inCat->GetLocation().mX > GetLocation().mX)
	{
		inCat->SetLocation(Vector3(inCat->GetLocation().mX - GetCollisionRadius(), inCat->GetLocation().mY, inCat->GetLocation().mZ));
	}

	if (inCat->GetLocation().mY < GetLocation().mY)
	{
		inCat->SetLocation(Vector3(inCat->GetLocation().mX, inCat->GetLocation().mY + GetCollisionRadius(), inCat->GetLocation().mZ));
	}
	else if (inCat->GetLocation().mY > GetLocation().mY)
	{
		inCat->SetLocation(Vector3(inCat->GetLocation().mX, inCat->GetLocation().mY - GetCollisionRadius(), inCat->GetLocation().mZ));
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