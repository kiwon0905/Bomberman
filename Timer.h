#pragma once

#include <chrono>

class Timer
{
private:
	std::chrono::high_resolution_clock::time_point startTime;
public:
	Timer::Timer(): startTime(std::chrono::high_resolution_clock::now()){}

	~Timer(){}

	typedef std::chrono::duration<double> sec;

	double Timer::getElapsedTime()
	{
		return std::chrono::duration_cast<sec>(std::chrono::high_resolution_clock::now()-startTime).count();
	}

	void Timer::restart()
	{
		startTime=std::chrono::high_resolution_clock::now();
	}
};

