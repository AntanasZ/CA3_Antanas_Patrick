/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatPCH.hpp"

Pickup::Pickup() 
{
	SetScale(GetScale() * 0.5f);
	SetCollisionRadius(30.f);
}


bool Pickup::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;
	return false;
}


uint32_t Pickup::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EMRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		Vector3 velocity = GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		inOutputStream.Write(GetScale());

		inOutputStream.Write(IsFacingRight());
		
		inOutputStream.Write(GetSpriteNumber());

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

void Pickup::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetLocation(location);

		Vector3 velocity;
		inInputStream.Read(velocity.mX);
		inInputStream.Read(velocity.mY);
		SetVelocity(velocity);

		float scale;
		inInputStream.Read(scale);
		SetScale(scale);

		bool facingRight;
		inInputStream.Read(facingRight);
		SetFacingRight(facingRight);

		sf::Int8 spriteNumber;
		inInputStream.Read(spriteNumber);
		SetSpriteNumber(spriteNumber);
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}
}

void Pickup::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SetLocation(GetLocation() + mVelocity * deltaTime);
}


