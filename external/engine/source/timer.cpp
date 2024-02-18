#include <Timer.h>

void Timer::Start()
{
	Started = true;

	StartTicks = std::chrono::steady_clock::now();
	PauseTicks = {};
}


void Timer::Pause()
{
	if (Started && !Paused)
	{
		Running = false;
        Paused = true;
		PauseTicks = std::chrono::steady_clock::now() - StartTicks;
		StartTicks = {};
	}
    else
    {
        Paused = false;
        Running = true;
		StartTicks = std::chrono::steady_clock::now() - PauseTicks;
		PauseTicks = {};
    }
}

void Timer::Stop()
{
	Started = false;
	Paused = false;

	StartTicks = {};
	PauseTicks = {};
}


bool Timer::IsPaused()
{
	return Paused && Started;
}

bool Timer::IsActive()
{
	return Started;
}

uint32_t Timer::GetMilliseconds()
{
	if (Started)
	{
		if (Running)
            return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - StartTicks).count();
		else
			return std::chrono::duration_cast<std::chrono::milliseconds>(PauseTicks).count();
	}
	else
		return 0;
}
