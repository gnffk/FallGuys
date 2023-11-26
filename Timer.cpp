#include "Timer.h"
#include <sstream>
#include <thread>

CTimer::CTimer(std::string Title) : last_time{ std::chrono::steady_clock::now() }, accm_time{ std::chrono::seconds{ 0 } }, fps{ 0 }, frame{ 0 }, Title{ Title }
{
}

float CTimer::Tick(int fps_value)		// ��� �ð� ����, 1 Frame�� �� �ѹ� ȣ��Ǿ�� ��
{
	if (fps_value > 0 and accm_time.count() / 1'000'000'000. * fps_value < frame)		// ������ ����
		std::this_thread::sleep_until(last_time + std::chrono::nanoseconds{ static_cast<int>(1. / fps_value * 1'000'000'000.) });

	++frame;
	auto now_time = std::chrono::steady_clock::now();
	auto elapsed_time = now_time - last_time;
	accm_time += elapsed_time;
	last_time = now_time;
	if (accm_time >= std::chrono::seconds{ 1 }) {			// �ʴ� �ѹ��� FPS ǥ��
		float over_time = accm_time.count() / 1'000'000'000.;
		fps = static_cast<int>(round(frame * (1.f / over_time)));
		frame -= fps;
		accm_time -= std::chrono::seconds{ 1 };

		std::stringstream title;
		title << Title << " - (" << fps << "FPS)";
		glutSetWindowTitle(title.str().c_str());
	}

	return elapsed_time.count() / 1'000'000'000.;		// �����ʸ� �ʷ� �ٲ��ش�.
}
