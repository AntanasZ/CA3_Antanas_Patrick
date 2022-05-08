class PlatformClient : public Platform
{
public:
	static GameObjectPtr StaticCreate() { return GameObjectPtr(new PlatformClient()); }

protected:
	PlatformClient();

private:
	SpriteComponentPtr mSpriteComponent;
};

