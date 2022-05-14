class DiverServer : public Diver
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new DiverServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;
	virtual void Update() override;

protected:
	DiverServer();

private:
	float mTimeToDie;

	void HandleShooting();

	float		mTimeOfNextShot;
	float		mTimeBetweenShots;
};