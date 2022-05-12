#include "RoboCatPCH.hpp"

Boat::Boat()
{
	SetScale(GetScale() * 0.5f);
	SetCollisionRadius(20.f);

	//Add initial velocity to boat
	SetVelocity(Vector3(0.f, 0.f, 0));
}


bool Boat::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;
	return false;
}


uint32_t Boat::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
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

void Boat::Read(InputMemoryBitStream& inInputStream)
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
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}
}

void Boat::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SetLocation(GetLocation() + mVelocity * deltaTime);
}