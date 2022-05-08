class Platform : public GameObject
{
public:
	CLASS_IDENTIFICATION('PLAT', GameObject)

	static GameObject* StaticCreate() { return new Platform(); }
	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	Platform() = default;
};

