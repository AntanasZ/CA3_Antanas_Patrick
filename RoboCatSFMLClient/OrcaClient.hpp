/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class OrcaClient : public Orca
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new OrcaClient()); }

protected:
	OrcaClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
