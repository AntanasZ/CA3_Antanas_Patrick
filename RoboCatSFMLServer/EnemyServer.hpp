class EnemyServer : public Enemy
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new EnemyServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;
	virtual void Update() override;

protected:
	EnemyServer();

private:
	float mTimeToDie;
};