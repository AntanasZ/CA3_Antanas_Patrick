#include "RoboCatPCH.hpp"

const float WORLD_HEIGHT = 692.f;
const float WORLD_WIDTH = 1280.f;

Player::Player() :
	GameObject(),
	mMaxRotationSpeed(100.f),
	mMaxLinearSpeed(5000.f),
	mVelocity(Vector3::Zero),
	mVelocityLeftRight(Vector3::Zero),
	mWallRestitution(0.1f),
	mPlayerRestitution(0.1f),
	mThrustDir(0.f),
	mThrustLeftRight(0.f),
	mPlayerId(0),
	mIsShooting(false),
	mHealth(10),
	mInvulnerabilityCountdown(0.f),
	mIsInvulnerable(false)
{
	SetCollisionRadius(50.f);
}

void Player::ProcessInput(float inDeltaTime, const InputState& inInputState)
{
	//process our input....

	//turning...
	//float newRotation = GetRotation() + inInputState.GetDesiredHorizontalDelta() * mMaxRotationSpeed * inDeltaTime;
	//SetRotation(newRotation);

	//moving...
	float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	float inputLeftRightDelta = inInputState.GetDesiredHorizontalDelta();

	mThrustDir = inputForwardDelta;


	mThrustLeftRight = inputLeftRightDelta;

	mIsShooting = inInputState.IsShooting();
}

void Player::AdjustVelocityByThrust(float inDeltaTime)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 forwardVector = GetForwardVector();//(0, -sqrtf(2.0f * 30 * 2), 0);
	mVelocity = forwardVector * (mThrustDir  * inDeltaTime * mMaxLinearSpeed);

	Vector3 leftRightVector(1, 0, 0);
	mVelocityLeftRight = leftRightVector * (mThrustLeftRight * inDeltaTime * mMaxLinearSpeed);

}

void Player::SimulateMovement(float inDeltaTime)
{
	
	//simulate us...
	AdjustVelocityByThrust(inDeltaTime);

	SetLocation(GetLocation() + mVelocity * inDeltaTime);
	SetLocation(GetLocation() + mVelocityLeftRight * inDeltaTime);
	
	//Add gravity to player
	//SetVelocity(Vector3(mVelocityLeftRight.mX, mVelocity.mY, 0));
	//SetVelocity(Vector3(mVelocityLeftRight.mX, mVelocity.mY, 0));

	//Accelerate(Vector3(0, 981.f, 0));
	if(mIsInvulnerable)
	{
		mInvulnerabilityCountdown += inDeltaTime;
	}

	if(mInvulnerabilityCountdown > 5.f)
	{
		mIsInvulnerable = false;
		mInvulnerabilityCountdown = 0.f;
	}
	

	//SetVelocity(Vector3(mVelocityLeftRight.mX, 981.f * inDeltaTime, 0));

	ProcessCollisions();
}

void Player::SetInvulnerable(bool value)
{
	mIsInvulnerable = value;
}

bool Player::GetInvulnerable()
{
	return mIsInvulnerable;
}



void Player::Update()
{
	
}

void Player::ProcessCollisions()
{
	//right now just bounce off the sides..
	ProcessCollisionsWithScreenWalls();

	float sourceRadius = GetCollisionRadius();
	Vector3 sourceLocation = GetLocation();

	//now let's iterate through the world and see what we hit...
	//note: since there's a small number of objects in our game, this is fine.
	//but in a real game, brute-force checking collisions against every other object is not efficient.
	//it would be preferable to use a quad tree or some other structure to minimize the
	//number of collisions that need to be tested.
	for (auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt)
	{
		GameObject* target = goIt->get();
		
		if (target != this && !target->DoesWantToDie())
		{
			//simple collision test for spheres- are the radii summed less than the distance?
			Vector3 targetLocation = target->GetLocation();
			float targetRadius = target->GetCollisionRadius();

			Vector3 delta = targetLocation - sourceLocation;
			float distSq = delta.LengthSq2D();
			float collisionDist = (sourceRadius + targetRadius);
			if (distSq < (collisionDist * collisionDist))
			{
				//first, tell the other guy there was a collision with a player, so it can do something...

				if (target->HandleCollisionWithPlayer(this))
				{
					//okay, you hit something!
					//so, project your location far enough that you're not colliding
					Vector3 dirToTarget = delta;
					dirToTarget.Normalize2D();
					Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;

					//if other object is a player, it might have velocity, so there might be relative velocity...
					Player* targetPlayer = target->GetAsPlayer();
					if (targetPlayer)
					{
						//relVel -= targetPlayer->mVelocity;
					}
					else
					{
						//important note- we only move this player. the other player can take care of moving itself
						SetLocation(targetLocation - acceptableDeltaFromSourceToTarget);


						Vector3 relVel = mVelocity;

						//got vel with dir between objects to figure out if they're moving towards each other
					    //and if so, the magnitude of the impulse ( since they're both just balls )
						float relVelDotDir = Dot2D(relVel, dirToTarget);

						if (relVelDotDir > 0.f)
						{
							Vector3 impulse = relVelDotDir * dirToTarget;

							mVelocity -= impulse * 2.f;
							mVelocity *= mWallRestitution;
						}
					}
				}
			}
		}
	}

}

void Player::ProcessCollisionsWithScreenWalls()
{
	Vector3 location = GetLocation();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	float radius = GetCollisionRadius();

	//if the player collides against a wall, the quick solution is to push it off
	if ((y + radius) >= WORLD_HEIGHT && vy > 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = WORLD_HEIGHT - radius;
		SetLocation(location);
	}
	else if (y - radius <= 0 && vy < 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = radius;
		SetLocation(location);
	}

	if ((x + radius) >= WORLD_WIDTH && vx > 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = WORLD_WIDTH - radius;
		SetLocation(location);
	}
	else if (x - radius <= 0 && vx < 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = radius;
		SetLocation(location);
	}
}

uint32_t Player::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetPlayerId());

		writtenState |= ECRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = mVelocity;
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	//always write mThrustDir- it's just two bits
	if (mThrustDir != 0.f)
	{
		inOutputStream.Write(true);
		inOutputStream.Write(mThrustDir > 0.f);
	}
	else
	{
		inOutputStream.Write(false);
	}

	if (inDirtyState & ECRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetColor());

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Health)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mHealth, 4);

		writtenState |= ECRS_Health;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;


}