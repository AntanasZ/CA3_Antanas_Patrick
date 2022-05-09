enum ESharkControlType
{
	ESCT_Human,
	ESCT_AI
};

class PlayerServer : public Player
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PlayerServer()); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetSharkControlType(ESharkControlType inSharkControlType) { mSharkControlType = inSharkControlType; }

	void TakeDamage(int inDamagingPlayerId);

protected:
	PlayerServer();

private:

	void HandleShooting();

	ESharkControlType	mSharkControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};

