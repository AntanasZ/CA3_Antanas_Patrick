typedef shared_ptr< sf::Texture > TexturePtr;
typedef shared_ptr<sf::Font> FontPtr;

class SpriteComponent
{
public:

	SpriteComponent(GameObject* inGameObject);
	~SpriteComponent();

	void SetTexture(TexturePtr inTexture, bool resetting);
	virtual sf::Sprite& GetSprite();
	GameObject* GetGameObject() { return mGameObject; }
	void UpdateTexture();


protected:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;
	bool mHasResetSprite = false;
};

typedef shared_ptr< SpriteComponent >	SpriteComponentPtr;

