class BoatClient : public Boat
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BoatClient()); }

protected:
	BoatClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
