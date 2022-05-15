/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
typedef GameObjectPtr(*GameObjectCreationFunc)();

class GameObjectRegistry
{
public:

	static void StaticInit();

	static std::unique_ptr< GameObjectRegistry > sInstance;

	void RegisterCreationFunction(uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction);

	GameObjectPtr CreateGameObject(uint32_t inFourCCName);

private:

	GameObjectRegistry();

	unordered_map< uint32_t, GameObjectCreationFunc > mNameToGameObjectCreationFunctionMap;
};

