class Octopus : public GameObject
{
public:
	CLASS_IDENTIFICATION('OCTO', GameObject)

	enum EOctopusReplicationState
	{
		EMRS_Pose = 1 << 0,
		EMRS_Color = 1 << 1,

		EMRS_AllState = EMRS_Pose | EMRS_Color
	};

	static	GameObject* StaticCreate() { return new Octopus(); }

	virtual	Octopus* GetAsOctopus() override { return this; }

	virtual uint32_t	GetAllStateMask()	const override { return EMRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;

	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;

	virtual void Update() override;

	void SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity() const { return mVelocity; }

protected:
	Octopus();

private:
	Vector3	mVelocity;
};

typedef shared_ptr< Octopus >	OctopusPtr;

