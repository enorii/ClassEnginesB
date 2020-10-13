#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();
	void start();
	void updateFrameTicks();
	float getDeltaTime() const;
	unsigned int getSleepTime(const unsigned int fps_);
	float getCurrentTicks() const;

private:
	unsigned int prevTicks, currentTicks;
};


#endif //TIMER_H