/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatPCH.hpp"

Projectile::Projectile() :
	mMuzzleSpeed(300.f),
	mVelocity(Vector3::Zero),
	mPlayerId(0)
{
	SetScale(GetScale() * 0.9f);
	SetCollisionRadius(20.f);
}

uint32_t Projectile::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EYRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		Vector3 velocity = GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		//inOutputStream.Write(GetRotation());

		inOutputStream.Write(GetScale());

		writtenState |= EYRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EYRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EYRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EYRS_PlayerId)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPlayerId, 8);

		writtenState |= EYRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return writtenState;
}



bool Projectile::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;

	//you hit a player, so look like you hit a player
	return false;
}


void Projectile::InitFromShooter(Player* inShooter)
{
	SetColor(inShooter->GetColor());
	SetPlayerId(inShooter->GetPlayerId());

	Vector3 forward = inShooter->GetForwardVector();
	SetVelocity(inShooter->GetVelocity() + forward * mMuzzleSpeed);
	SetLocation(inShooter->GetLocation() /* + forward * 0.55f */);

	SetRotation(inShooter->GetRotation());
}

void Projectile::InitFromBoat(Boat* inBoat)
{
	SetVelocity(Vector3(0, 300.f, 0));
	SetLocation(inBoat->GetLocation() /* + forward * 0.55f */);
}

void Projectile::InitFromDiver(Diver* inDiver)
{
	Vector3 forward = inDiver->GetForwardVector();

	if (inDiver->GetVelocity().mX > 0)
	{
		SetVelocity(Vector3(inDiver->GetVelocity().mX + 80.f, 0.f, 0.f));
		SetLocation(Vector3(inDiver->GetLocation().mX + 20.f,
			inDiver->GetLocation().mY, inDiver->GetLocation().mZ));
	}
	else
	{
		SetVelocity(Vector3(inDiver->GetVelocity().mX - 80.f, 0.f, 0.f));
		SetLocation(Vector3(inDiver->GetLocation().mX -20.f, 
			inDiver->GetLocation().mY, inDiver->GetLocation().mZ));
	}
}

void Projectile::Update()
{
	//SetVelocity(Vector3(0, 981.f, 0));

	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetLocation(GetLocation() + mVelocity * deltaTime);

	
	//we'll let the players handle the collisions
}

