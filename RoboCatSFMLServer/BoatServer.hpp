class BoatServer : public Boat
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BoatServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;
	virtual void Update() override;

protected:
	BoatServer();

private:
	float mTimeToDie;

	void HandleShooting();

	float		mTimeOfNextShot;
	float		mTimeBetweenShots;
};