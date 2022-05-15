/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class PlatformClient : public Platform
{
public:
	static GameObjectPtr StaticCreate() { return GameObjectPtr(new PlatformClient()); }

protected:
	PlatformClient();

private:
	SpriteComponentPtr mSpriteComponent;
};

