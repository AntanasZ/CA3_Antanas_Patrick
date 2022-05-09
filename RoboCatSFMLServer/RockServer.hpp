class RockServer : public Rock
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new RockServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;
	virtual void Update() override;

protected:
	RockServer();

private:
	float mTimeToDie;
};

