#ifndef __j1TIMER_H__
#define __j1TIMER_H__

#include "Globals.h"
#include "SDL/include/SDL.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	Uint32 Read() const;
	float ReadSec() const;

private:

	Uint32	started_at = 0;
};

#endif //__j1TIMER_H__