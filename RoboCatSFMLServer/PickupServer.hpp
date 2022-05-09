class PickupServer : public Pickup
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PickupServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithPlayer(Player* inPlayer) override;
	virtual void Update() override;

protected:
	PickupServer();

private:
	float mTimeToDie;
};

