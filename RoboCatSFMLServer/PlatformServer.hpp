class PlatformServer : public Platform
{
public:
	static GameObjectPtr StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PlatformServer()); }
	//virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	PlatformServer();
};

