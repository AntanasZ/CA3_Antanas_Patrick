/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
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

	void TakeDamage(int inDamagingPlayerId, int damage_amount);

protected:
	PlayerServer();

private:

	void HandleShooting();

	ESharkControlType	mSharkControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};

