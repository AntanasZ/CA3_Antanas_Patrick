/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class ProjectileClient : public Projectile
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new ProjectileClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	ProjectileClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
