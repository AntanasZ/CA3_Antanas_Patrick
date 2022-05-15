/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>
#include "RoboCatPCH.hpp"

bool Move::Write(OutputMemoryBitStream& inOutputStream) const
{
	mInputState.Write(inOutputStream);
	inOutputStream.Write(mTimestamp);

	return true;
}

bool Move::Read(InputMemoryBitStream& inInputStream)
{
	mInputState.Read(inInputStream);
	inInputStream.Read(mTimestamp);

	return true;
}

