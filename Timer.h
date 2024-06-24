#pragma once

#include <chrono>

class Timer {
public:
    static void start();
    static void update();
    static float getDeltaTime();
    static float getFps();

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> mLastTime;
    static float mDeltaTime;
    static float mFps;
    static int mFrameCount;
    static float mElapsedTime;
};

