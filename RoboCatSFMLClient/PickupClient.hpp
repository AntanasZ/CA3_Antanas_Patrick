/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class PickupClient : public Pickup
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new PickupClient()); }

protected:
	PickupClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
