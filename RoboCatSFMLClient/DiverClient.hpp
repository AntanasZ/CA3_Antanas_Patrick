/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class DiverClient : public Diver
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new DiverClient()); }

protected:
	DiverClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
