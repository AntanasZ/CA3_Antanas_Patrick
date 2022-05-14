class OctopusClient : public Octopus
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new OctopusClient()); }

protected:
	OctopusClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
