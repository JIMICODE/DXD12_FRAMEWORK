#pragma once

#ifndef GAMETIMER_H_
#define GAMETIMER_H_

#include<Windows.h>

class GameTimer
{
public:
	GameTimer();

	float DeltaTime() const; // in seconds
	float TotalTime() const; // int seconds

	void Reset(); // call defore message loop.
	void Start(); // call when unpauseed.
	void Stop(); // call when paused.
	void Tick(); // call every frame

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif // !CLASS_TIMER
