/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatPCH.hpp"

Rock::Rock()
{
	//SetScale(GetScale() * 0.5f);
	SetCollisionRadius(60.f);

	//Add gravity to pickup
	SetVelocity(Vector3(0, 250.f, 0));
}

bool Rock::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;
	return false;
}

uint32_t Rock::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EMRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= EMRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EMRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EMRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	return writtenState;
}

void Rock::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetLocation(location);

		float rotation;
		inInputStream.Read(rotation);
		SetRotation(rotation);
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}
}

void Rock::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SetLocation(GetLocation() + mVelocity * deltaTime);
}
