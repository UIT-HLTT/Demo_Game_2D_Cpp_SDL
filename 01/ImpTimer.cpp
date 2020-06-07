#include "ImpTimer.h"

ImpTimer::ImpTimer(void)
{
	iStartTick = 0;
	iPausedTick = 0;
	bIsPaused = false;
	bIsStarted = false;
}

ImpTimer::~ImpTimer(void)
{
	Free();
}

void ImpTimer::Start()
{
	bIsStarted = true;
	bIsStarted = false;
	iStartTick = SDL_GetTicks();
}

void ImpTimer::Stop()
{
	bIsPaused = false;
	bIsStarted = true;
}

void ImpTimer::Paused()
{
	if (bIsStarted == true && bIsPaused == false)
	{
		bIsPaused = true;
		iPausedTick = SDL_GetTicks() - iStartTick;
	}
}

void ImpTimer::Unpaused()
{
	if (bIsPaused == true)
	{
		bIsPaused = false;
		iStartTick = SDL_GetTicks() - iPausedTick;
		iPausedTick = 0;
	}
}

int ImpTimer::GetTicks()
{
	if (bIsStarted == true)
	{
		if (bIsPaused == true)
		{
			return iPausedTick;
		}
		else return SDL_GetTicks() - iStartTick;
	}
	return 0;
}

bool ImpTimer::IsStarted()
{
	return bIsStarted;
}

bool ImpTimer::IsPaused()
{
	return bIsPaused;
}

void ImpTimer::Free()
{
	iStartTick = 0;
	iPausedTick = 0;
	bIsPaused = false;
	bIsStarted = false;
}