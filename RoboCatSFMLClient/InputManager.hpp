/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class InputManager
{
public:
	static void StaticInit();
	static unique_ptr< InputManager >	sInstance;

	void HandleInput(EInputAction inInputAction, int inKeyCode);

	const InputState& GetState()	const { return mCurrentState; }

	MoveList& GetMoveList() { return mMoveList; }

	const Move* GetAndClearPendingMove() { auto toRet = mPendingMove; mPendingMove = nullptr; return toRet; }

	void				Update();

private:

	InputState							mCurrentState;

	InputManager();

	bool				IsTimeToSampleInput();
	const Move& SampleInputAsMove();

	MoveList		mMoveList;
	float			mNextTimeToSampleInput;
	const Move* mPendingMove;
};

