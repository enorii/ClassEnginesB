#include "Timer.h"



Timer::Timer(){
	prevTicks = 0;
	currentTicks = 0;
}


Timer::~Timer(){

}

void Timer::start() {
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();
}

void Timer::updateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::getDeltaTime() const {
	return static_cast<float>(currentTicks - prevTicks) / 100.00f;
}

unsigned int Timer::getSleepTime(const unsigned int fps_) {
	unsigned int milliPerFrame = 1000 / fps_;
	if (milliPerFrame == 0) {
		return 0;
	}
	unsigned int sleepTime = milliPerFrame - SDL_GetTicks();
	if (sleepTime > milliPerFrame) { //check if sleep or milli time is bigger(or smaller? idk)
		return milliPerFrame;
	}
	return sleepTime;
}

float Timer::getCurrentTicks() const {
	return static_cast<float>(currentTicks);
}