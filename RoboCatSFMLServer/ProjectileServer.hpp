class ProjectileServer : public Projectile
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new ProjectileServer()); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithCat(RoboCat* inCat) override;

	virtual void Update() override;

protected:
	ProjectileServer();

private:
	float mTimeToDie;

};
