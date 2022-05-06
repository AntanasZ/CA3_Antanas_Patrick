class PickupClient : public Pickup
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new PickupClient()); }

protected:
	PickupClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
