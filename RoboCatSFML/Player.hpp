class Player : public GameObject
{
public:
	CLASS_IDENTIFICATION('PLAY', GameObject)

	enum EPlayerReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId | ECRS_Health
	};


	static	GameObject* StaticCreate() { return new Player(); }

	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	virtual	Player* GetAsPlayer() override { return this; }

	virtual void Update() override;

	void ProcessInput(float inDeltaTime, const InputState& inInputState);
	void SimulateMovement(float inDeltaTime);

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }
	void Accelerate(const Vector3 inVelocity) { mVelocity += inVelocity; }

	void SetInvulnerable(bool value);
	bool GetInvulnerable();

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	Player();

private:


	void	AdjustVelocityByThrust(float inDeltaTime);

	Vector3				mVelocity;
	Vector3 mVelocityLeftRight;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mPlayerRestitution;


	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;
	float mThrustLeftRight;
	int					mHealth;

	bool				mIsShooting;
	bool mIsInvulnerable;
	float mInvulnerabilityCountdown;
};

typedef shared_ptr< Player >	PlayerPtr;

