#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include "Header.h"

class ImpTimer
{
public:
	ImpTimer(void);
	~ImpTimer(void);

	void Start();
	void Stop();
	void Paused();
	void Unpaused();
	bool IsStarted();
	bool IsPaused();
	void Free();

	/* ------- set & get ------- */
	int GetTicks();

private:
	int iStartTick;
	int iPausedTick;

	bool bIsPaused;
	bool bIsStarted;
};

#endif