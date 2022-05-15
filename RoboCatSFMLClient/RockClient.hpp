/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class RockClient : public Rock
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new RockClient()); }

protected:
	RockClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};

