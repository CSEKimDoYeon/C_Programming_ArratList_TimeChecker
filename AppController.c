#include "AppController.h"
#include "SortedArrayList.h"
#include "UnsortedArrayList.h"
#include "Messages.h"
#include "Timer.h"
#include "Common.h"
#include "ParameterSet.h"

#include <stdio.h>

#define MIN_TEST_SIZE 1000
#define NUMBER_OF_TESTS 5
#define INTERVAL_SIZE 1000

struct _AppController {
	ParameterSet* _parameterSet;
	int* _testData;
	Timer* _timer;
}; AppController* AppController_new(void) {
	AppController* _this = (AppController*)malloc(sizeof(AppController));
	_this->_parameterSet = ParameterSet_new(); 
	return _this;
} // AppController ����ü ����.

void AppController_delete(AppController* _this) {
	free(_this);
} // AppController ����ü ����(��ȯ).

void AppController_run(AppController* _this)
{
	AppIO_out(MSG_StartPerformanceMeasuring);
	AppController_initPerformanceMeasurement(_this);
	// ���� ���� ����.
	int numberOfTests = ParameterSet_numberOfTests(_this->_parameterSet);
	int maxTestSize = ParameterSet_maxTestSize(_this->_parameterSet);
	int intervalSize = ParameterSet_intervalSize(_this->_parameterSet);
	// ParameterSet�� ������ ���� size ����.
	AppIO_out(MSG_TitleForUnsortedArrayList);
	int testSize = ParameterSet_minTestSize(_this->_parameterSet);
	for (int i = 0; i < numberOfTests; i++) { 
		// UnsortedArrayList ���� ���� ����.
		UnsortedArrayList* listForTest = UnsortedArrayList_new(maxTestSize);
		double timeForAdd = AppController_timeForUnsortedArrayList_add(_this, listForTest, testSize);
		double timeForMin = AppController_timeForUnsortedArrayList_min(_this, listForTest, testSize);
		double timeForRemoveMax = AppController_timeForUnsortedArrayList_removeMax(_this, listForTest, testSize);
		AppController_showResults(_this, testSize, timeForAdd, timeForMin, timeForRemoveMax); 
		UnsortedArrayList_delete(listForTest); // �� ����Ŭ �׽�Ʈ�� ������ ����Ʈ ����.
		testSize += intervalSize; // IntervalSize ��ŭ ���ذ��� ��� ����.
	}

	AppIO_out(MSG_TitleForSortedArrayList);
	testSize = ParameterSet_minTestSize(_this->_parameterSet);
	for (int i = 0; i < numberOfTests; i++) {
		// SortedArrayList ���� ���� ����.
		SortedArrayList* listForTest = SortedArrayList_new(maxTestSize);
		double timeForAdd = AppController_timeForSortedArrayList_add(_this, listForTest, testSize);
		double timeForMin = AppController_timeForSortedArrayList_min(_this, listForTest, testSize);
		double timeForRemoveMax = AppController_timeForSortedArrayList_removeMax(_this, listForTest, testSize); 
		AppController_showResults(_this, testSize, timeForAdd, timeForMin, timeForRemoveMax);
		SortedArrayList_delete(listForTest); // �� ����Ŭ �׽�Ʈ�� ������ ����Ʈ ����.
 		testSize += intervalSize; // IntervalSize ��ŭ ���ذ��� ��� ����.
	}
	AppIO_out(MSG_EndPerformanceMeasuring);
}void AppController_generateTestDataByRandomNumbers(AppController* _this)
{ // �׽�Ʈ�� ����� ���� ��� ����.
	int maxTestSize = MIN_TEST_SIZE + INTERVAL_SIZE * (NUMBER_OF_TESTS - 1);
	srand((unsigned)time(NULL));
	for (int i = 0; i < maxTestSize; i++) {
		_this->_testData[i] = rand();
	} // �ִ� ������ ��ŭ rand() �Լ� ȣ��.
}

double AppController_timeForUnsortedArrayList_add(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArray�� �����͸� ����.
	Timer* timer = Timer_new();
	// ���� �۾��� �۾��ð��� ������ timer ��ü ����.
	long duration = 0;
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer); // data �߰� �� timer ����.
		if (!UnsortedArrayList_isFull(aList)) {
			UnsortedArrayList_add(aList, _this->_testData[i]);
			// ArrayList�� Full�� �ƴ� �� ���� ����.
		}
		Timer_stop(timer); // �۾��� ������ Ÿ�̸� ����.
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	return duration;
}

double AppController_timeForUnsortedArrayList_removeMax(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArrayList���� �ִ밪 ����.
	Element max;
	long duration = 0;
	Timer* timer = Timer_new();
	// �ִ밪 ���� �۾� �� �۾��ð� ���� ����.
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer);
		if (!UnsortedArrayList_isEmpty(aList)) {
			max = UnsortedArrayList_removeMax(aList);
		}
		Timer_stop(timer);
		duration += Timer_duration(timer);
	}
	Timer_delete(timer); 
	// ������ ������ Timer ��ü ����.
	return duration;
}

void AppController_showResults(AppController* _this,	int aTestSize, double aTimeForAdd, double aTimeForMin, double aTimeForRemoveMax)
{	// �۾��� ��� ���� �� ����� ���� ������� ȭ�鿡 ���.
	char results[255];
	sprintf_s(
		results, sizeof(results),
		"ũ��: % 4d, ���� : % 6ld, �ּҰ���� : % 7ld, �ִ밪���� : % 7ld\n",
		aTestSize, (long)aTimeForAdd, (long)aTimeForMin, (long)aTimeForRemoveMax);
	AppIO_out(results);
}void AppController_initPerformanceMeasurement(AppController* _this) {
	// ���� ���� ���� �Լ�. define �Ǿ��ִ� �������� ParameterSet�� ����.
	ParameterSet_setMinTestSize(_this->_parameterSet, MIN_TEST_SIZE);
	ParameterSet_setIntervalSize(_this->_parameterSet, INTERVAL_SIZE);
	ParameterSet_setNumberOfTests(_this->_parameterSet, NUMBER_OF_TESTS);
	
	_this->_testData = NewVector(int, ParameterSet_maxTestSize(_this->_parameterSet)); 
	AppController_generateTestDataByRandomNumbers(_this);
	// �� �迭�� �����ϰ� ������ ����.
}double AppController_timeForUnsortedArrayList_min
(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArrayList���� �ּҰ��� ã�� �Լ�.
	Element min;
	double duration = 0;
	Timer* timer = Timer_new();
	// �ּҰ� ã�� �۾� �� �ð� ������ ���� Ÿ�̸� ����.
	for (int i = 0; i < aTestSize; i++) {
		// �̰��� ���������� ����Ʈ�� ������ ������ ���� ���¿��� ������ ������ �ݺ��Ѵ�
		Timer_start(timer);
		if (!UnsortedArrayList_isEmpty(aList)) {
			min = UnsortedArrayList_min(aList);
		}
		Timer_stop(timer); 
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	// ������ ��� ������ Timer ����. 
	return duration;
}

double AppController_timeForSortedArrayList_add
(AppController* _this, SortedArrayList* aList, int aTestSize) { 
	// SortedArray�� rand ���� ����.
	Timer* timer = Timer_new(); // ���� �� �ð� ����.
	long duration = 0;
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer);
		if (!SortedArrayList_isFull(aList)) {
			SortedArrayList_add(aList, _this->_testData[i]);
		}
		Timer_stop(timer);
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	// �ð� ������ ������ Timer ��ü ����.
	return duration;
}

double AppController_timeForSortedArrayList_min
(AppController* _this, SortedArrayList* aList, int aTestSize) {
	// SortedArryList���� �ּҰ��� ã�� �Լ�.
	Element min;
	double duration = 0;
	Timer* timer = Timer_new();
	for (int i = 0; i < aTestSize; i++) {
		// �̰��� ���������� ����Ʈ�� ������ ������ ���� ���¿��� ������ ������ �ݺ��Ѵ�
		Timer_start(timer);
		if (!SortedArrayList_isEmpty(aList)) {
			min = SortedArrayList_min(aList);
		}
		Timer_stop(timer);
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	return duration;
}

double AppController_timeForSortedArrayList_removeMax
(AppController* _this, SortedArrayList* aList, int aTestSize) {
	// SortedArrayList���� �ִ밪�� �����ϴ� �Լ�.
	Element max;
	long duration = 0;
	Timer* timer = Timer_new();
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer);
		if (!SortedArrayList_isEmpty(aList)) {
			max = SortedArrayList_removeMax(aList);
		}
		Timer_stop(timer);
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	return duration;
}