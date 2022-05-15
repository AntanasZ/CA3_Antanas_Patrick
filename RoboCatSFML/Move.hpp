/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
class Move
{
public:

	Move() {}

	Move(const InputState& inInputState, float inTimestamp, float inDeltaTime) :
		mInputState(inInputState),
		mTimestamp(inTimestamp),
		mDeltaTime(inDeltaTime)
	{}


	const InputState& GetInputState()	const { return mInputState; }
	float GetTimestamp()	const { return mTimestamp; }
	float GetDeltaTime()	const { return mDeltaTime; }

	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

private:
	InputState	mInputState;
	float		mTimestamp;
	float		mDeltaTime;
};


