#include "Timer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::mLastTime;
float Timer::mDeltaTime = 0.0f;
float Timer::mFps = 0.0f;
int Timer::mFrameCount = 0;
float Timer::mElapsedTime = 0.0f;

void Timer::start() {
    mLastTime = std::chrono::high_resolution_clock::now();
    mDeltaTime = 0.0f;
    mFps = 0.0f;
    mFrameCount = 0;
    mElapsedTime = 0.0f;
}

void Timer::update() {
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> elapsed = currentTime - mLastTime;
    mLastTime = currentTime;
    mDeltaTime = elapsed.count();

    mElapsedTime += mDeltaTime;
    mFrameCount++;

    if (mElapsedTime >= 1.0f) {
        mFps = mFrameCount / mElapsedTime;
        mFrameCount = 0;
        mElapsedTime = 0.0f;
    }
}

float Timer::getDeltaTime() {
    return mDeltaTime;
}

float Timer::getFps() {
    return mFps;
}