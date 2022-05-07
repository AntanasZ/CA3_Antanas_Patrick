#pragma once
class Enemy : public GameObject
{
public:
	CLASS_IDENTIFICATION('ENEM', GameObject)

		enum EPickupReplicationState
	{
		EMRS_Pose = 1 << 0,
		EMRS_Color = 1 << 1,

		EMRS_AllState = EMRS_Pose | EMRS_Color
	};

	static	GameObject* StaticCreate() { return new Enemy(); }

	virtual uint32_t	GetAllStateMask()	const override { return EMRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;

	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

	virtual void Update() override;

	void SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }

protected:
	Enemy();

private:
	Vector3	mVelocity;
};

