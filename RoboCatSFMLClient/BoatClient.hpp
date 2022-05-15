/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class BoatClient : public Boat
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BoatClient()); }

protected:
	BoatClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
