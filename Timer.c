#include "Timer.h"

Timer * Timer_new(void) { // �ð������� ���� Timer ��ü ����.
	Timer* _this = (Timer*)malloc(sizeof(Timer));
	QueryPerformanceFrequency(&(_this->_frequency)); // ���ļ�( 1�ʴ� �����Ǵ� ī��Ʈ ��)�� ���Ѵ�.
	return _this;
}
void Timer_delete(Timer* _this) { // �Ҹ���
	free(_this);
}
void Timer_start(Timer* _this) {
	QueryPerformanceCounter(&(_this->_startCounter)); // ���� �� ī��Ʈ�� ���Ѵ�.
}
void Timer_stop(Timer* _this) {
	QueryPerformanceCounter(&(_this->_stopCounter)); // ���� �� ī��Ʈ�� ���Ѵ�.
}
double Timer_duration(Timer* _this) {
	double elapsed = (double)(_this->_stopCounter.QuadPart - _this->_startCounter.QuadPart);
	return (elapsed * 1000000.0 / ((double)_this->_frequency.QuadPart));
	// ���� �ð��� ����ũ�� �� (micro second) �� ��ȯ�Ѵ�.
}