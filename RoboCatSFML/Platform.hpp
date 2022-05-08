class Platform : public GameObject
{
public:
	CLASS_IDENTIFICATION('PLAT', GameObject)

	enum EPlatformReplicationState
	{
		EMRS_Pose = 1 << 0,
		EMRS_Color = 1 << 1,

		EMRS_AllState = EMRS_Pose | EMRS_Color
	};

	static GameObject* StaticCreate() { return new Platform(); }
	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

	virtual uint32_t	GetAllStateMask()	const override { return EMRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	Platform();
};

