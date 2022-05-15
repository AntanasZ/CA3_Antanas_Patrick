/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr<TextureManager>		sInstance;

	TexturePtr	GetTexture(const string& inTextureName);

private:
	TextureManager();

	bool CacheTexture(string inName, const char* inFileName);

	unordered_map< string, TexturePtr >	mNameToTextureMap;
};

