class OrcaClient : public Orca
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new OrcaClient()); }

protected:
	OrcaClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
