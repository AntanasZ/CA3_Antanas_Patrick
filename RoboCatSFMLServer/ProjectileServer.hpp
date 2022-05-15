/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class ProjectileServer : public Projectile
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new ProjectileServer()); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithPlayer(Player* inPlayer) override;

	virtual void Update() override;

protected:
	ProjectileServer();

private:
	float mTimeToDie;

};

