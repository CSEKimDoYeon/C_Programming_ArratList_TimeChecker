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
} // AppController 구조체 생성.

void AppController_delete(AppController* _this) {
	free(_this);
} // AppController 구조체 삭제(반환).

void AppController_run(AppController* _this)
{
	AppIO_out(MSG_StartPerformanceMeasuring);
	AppController_initPerformanceMeasurement(_this);
	// 성능 측정 시작.
	int numberOfTests = ParameterSet_numberOfTests(_this->_parameterSet);
	int maxTestSize = ParameterSet_maxTestSize(_this->_parameterSet);
	int intervalSize = ParameterSet_intervalSize(_this->_parameterSet);
	// ParameterSet에 측정을 위한 size 저장.
	AppIO_out(MSG_TitleForUnsortedArrayList);
	int testSize = ParameterSet_minTestSize(_this->_parameterSet);
	for (int i = 0; i < numberOfTests; i++) { 
		// UnsortedArrayList 성능 측정 시작.
		UnsortedArrayList* listForTest = UnsortedArrayList_new(maxTestSize);
		double timeForAdd = AppController_timeForUnsortedArrayList_add(_this, listForTest, testSize);
		double timeForMin = AppController_timeForUnsortedArrayList_min(_this, listForTest, testSize);
		double timeForRemoveMax = AppController_timeForUnsortedArrayList_removeMax(_this, listForTest, testSize);
		AppController_showResults(_this, testSize, timeForAdd, timeForMin, timeForRemoveMax); 
		UnsortedArrayList_delete(listForTest); // 한 사이클 테스트가 끝나면 리스트 삭제.
		testSize += intervalSize; // IntervalSize 만큼 더해가며 계속 진행.
	}

	AppIO_out(MSG_TitleForSortedArrayList);
	testSize = ParameterSet_minTestSize(_this->_parameterSet);
	for (int i = 0; i < numberOfTests; i++) {
		// SortedArrayList 성능 측정 시작.
		SortedArrayList* listForTest = SortedArrayList_new(maxTestSize);
		double timeForAdd = AppController_timeForSortedArrayList_add(_this, listForTest, testSize);
		double timeForMin = AppController_timeForSortedArrayList_min(_this, listForTest, testSize);
		double timeForRemoveMax = AppController_timeForSortedArrayList_removeMax(_this, listForTest, testSize); 
		AppController_showResults(_this, testSize, timeForAdd, timeForMin, timeForRemoveMax);
		SortedArrayList_delete(listForTest); // 한 사이클 테스트가 끝나면 리스트 삭제.
 		testSize += intervalSize; // IntervalSize 만큼 더해가며 계속 진행.
	}
	AppIO_out(MSG_EndPerformanceMeasuring);
}void AppController_generateTestDataByRandomNumbers(AppController* _this)
{ // 테스트에 사용할 랜덤 상수 생성.
	int maxTestSize = MIN_TEST_SIZE + INTERVAL_SIZE * (NUMBER_OF_TESTS - 1);
	srand((unsigned)time(NULL));
	for (int i = 0; i < maxTestSize; i++) {
		_this->_testData[i] = rand();
	} // 최대 사이즈 만큼 rand() 함수 호출.
}

double AppController_timeForUnsortedArrayList_add(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArray에 데이터를 삽입.
	Timer* timer = Timer_new();
	// 삽입 작업시 작업시간을 측정할 timer 객체 생성.
	long duration = 0;
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer); // data 추가 및 timer 시작.
		if (!UnsortedArrayList_isFull(aList)) {
			UnsortedArrayList_add(aList, _this->_testData[i]);
			// ArrayList가 Full이 아닐 때 까지 삽입.
		}
		Timer_stop(timer); // 작업이 끝나면 타이머 종료.
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	return duration;
}

double AppController_timeForUnsortedArrayList_removeMax(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArrayList에서 최대값 삭제.
	Element max;
	long duration = 0;
	Timer* timer = Timer_new();
	// 최대값 삭제 작업 시 작업시간 측정 시작.
	for (int i = 0; i < aTestSize; i++) {
		Timer_start(timer);
		if (!UnsortedArrayList_isEmpty(aList)) {
			max = UnsortedArrayList_removeMax(aList);
		}
		Timer_stop(timer);
		duration += Timer_duration(timer);
	}
	Timer_delete(timer); 
	// 측정이 끝나면 Timer 객체 삭제.
	return duration;
}

void AppController_showResults(AppController* _this,	int aTestSize, double aTimeForAdd, double aTimeForMin, double aTimeForRemoveMax)
{	// 작업이 모두 끝난 후 저장된 측정 결과들을 화면에 출력.
	char results[255];
	sprintf_s(
		results, sizeof(results),
		"크기: % 4d, 삽입 : % 6ld, 최소값얻기 : % 7ld, 최대값삭제 : % 7ld\n",
		aTestSize, (long)aTimeForAdd, (long)aTimeForMin, (long)aTimeForRemoveMax);
	AppIO_out(results);
}void AppController_initPerformanceMeasurement(AppController* _this) {
	// 성능 측정 시작 함수. define 되어있는 설정값들 ParameterSet에 저장.
	ParameterSet_setMinTestSize(_this->_parameterSet, MIN_TEST_SIZE);
	ParameterSet_setIntervalSize(_this->_parameterSet, INTERVAL_SIZE);
	ParameterSet_setNumberOfTests(_this->_parameterSet, NUMBER_OF_TESTS);
	
	_this->_testData = NewVector(int, ParameterSet_maxTestSize(_this->_parameterSet)); 
	AppController_generateTestDataByRandomNumbers(_this);
	// 새 배열을 생성하고 데이터 삽입.
}double AppController_timeForUnsortedArrayList_min
(AppController* _this, UnsortedArrayList* aList, int aTestSize)
{ // UnsortedArrayList에서 최소값을 찾는 함수.
	Element min;
	double duration = 0;
	Timer* timer = Timer_new();
	// 최소값 찾기 작업 시 시간 측정을 위해 타이머 생성.
	for (int i = 0; i < aTestSize; i++) {
		// 이곳의 측정에서는 리스트의 내용이 변하지 않은 상태에서 동일한 행위를 반복한다
		Timer_start(timer);
		if (!UnsortedArrayList_isEmpty(aList)) {
			min = UnsortedArrayList_min(aList);
		}
		Timer_stop(timer); 
		duration += Timer_duration(timer);
	}
	Timer_delete(timer);
	// 측정이 모두 끝나면 Timer 삭제. 
	return duration;
}

double AppController_timeForSortedArrayList_add
(AppController* _this, SortedArrayList* aList, int aTestSize) { 
	// SortedArray에 rand 값을 삽입.
	Timer* timer = Timer_new(); // 삽입 시 시간 측정.
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
	// 시간 측정이 끝나면 Timer 객체 삭제.
	return duration;
}

double AppController_timeForSortedArrayList_min
(AppController* _this, SortedArrayList* aList, int aTestSize) {
	// SortedArryList에서 최소값을 찾는 함수.
	Element min;
	double duration = 0;
	Timer* timer = Timer_new();
	for (int i = 0; i < aTestSize; i++) {
		// 이곳의 측정에서는 리스트의 내용이 변하지 않은 상태에서 동일한 행위를 반복한다
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
	// SortedArrayList에서 최대값을 삭제하는 함수.
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