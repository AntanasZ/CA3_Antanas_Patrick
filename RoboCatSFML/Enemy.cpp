#include "RoboCatPCH.hpp"

Enemy::Enemy()
{
	SetScale(GetScale() * 0.5f);
	SetCollisionRadius(20.f);

	//Add initial velocity to enemy
	SetVelocity(Vector3(0.f, 0.f, 0));
}


bool Enemy::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;
	return false;
}


uint32_t Enemy::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
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

void Enemy::Read(InputMemoryBitStream& inInputStream)
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

void Enemy::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();
	SetLocation(GetLocation() + mVelocity * deltaTime);
}