class EnemyClient : public Enemy
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new EnemyClient()); }

protected:
	EnemyClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
