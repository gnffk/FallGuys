#pragma once

#include "stdafx.h"
#include <chrono>

class CTimer {
	std::chrono::steady_clock::time_point last_time;		// ���������� ȣ��� �ð�
	std::chrono::nanoseconds accm_time;
	int fps;
	int frame;

	std::string Title;

public:
	CTimer(std::string Title);

	float Tick(int fps_value);		// ��� �ð� ����, 1 Frame�� �� �ѹ� ȣ��Ǿ�� ��
};


