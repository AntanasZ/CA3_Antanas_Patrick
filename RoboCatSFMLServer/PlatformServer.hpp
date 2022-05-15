/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class PlatformServer : public Platform
{
public:
	static GameObjectPtr StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PlatformServer()); }
	//virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	PlatformServer();
};

