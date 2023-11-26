#pragma once

#include "stdafx.h"
#include <chrono>

class CTimer {
	std::chrono::steady_clock::time_point last_time;		// 마지막으로 호출된 시간
	std::chrono::nanoseconds accm_time;
	int fps;
	int frame;

	std::string Title;

public:
	CTimer(std::string Title);

	float Tick(int fps_value);		// 경과 시간 리턴, 1 Frame에 단 한번 호출되어야 함
};


