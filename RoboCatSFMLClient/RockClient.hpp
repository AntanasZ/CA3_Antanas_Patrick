class RockClient : public Rock
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new RockClient()); }

protected:
	RockClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};

