/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class OctopusClient : public Octopus
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new OctopusClient()); }

protected:
	OctopusClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
