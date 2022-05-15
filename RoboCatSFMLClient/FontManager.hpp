/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class FontManager
{
public:
	static void StaticInit();

	static std::unique_ptr<FontManager> sInstance;

	FontPtr GetFont(const string& p_fontName);

private:
	FontManager();

	bool CacheFont(string inName, const char* inFileName);

	unordered_map< string, FontPtr >	mNameToFontMap;
};

