#pragma once
#include <cstdint>
#include <chrono>
#include <ctime>
#include <iostream>

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> StartTicks;
	std::chrono::time_point<std::chrono::steady_clock> LastTick;
    std::chrono::steady_clock::duration PauseTicks;

	bool Started;
    bool Paused;
	bool Running;
public:
	Timer()
		: StartTicks({}), PauseTicks({}), Started(0), Paused(0), Running(0) {}

	void Start();
	void Pause();	
	void Stop();

	bool IsPaused();
	bool IsActive();
	uint32_t GetMilliseconds();
};