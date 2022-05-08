#include "RoboCatPCH.hpp"

Platform::Platform()
{
	
}

bool Platform::HandleCollisionWithCat(RoboCat* inCat)
{
	(void)inCat;
	return false;
}
