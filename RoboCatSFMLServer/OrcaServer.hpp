class OrcaServer : public Orca
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new OrcaServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;
	virtual void Update() override;

protected:
	OrcaServer();

private:
	float mTimeToDie;
};