class RockServer : public Rock
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new RockServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;
	virtual void Update() override;

protected:
	RockServer();

private:
	float mTimeToDie;
};

