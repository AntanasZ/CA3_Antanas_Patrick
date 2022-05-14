class DiverClient : public Diver
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new DiverClient()); }

protected:
	DiverClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
