#pragma once
#include "Common.h"
#include "UnsortedArrayList.h"
#include "SortedArrayList.h"

typedef struct _AppController AppController;


AppController* AppController_new(void);
void AppController_delete(AppController* _this);
void AppController_run(AppController* _this);
void AppController_generateTestDataByRandomNumbers(AppController* _this);

void AppController_showResults(AppController* _this,	int aTestSize, double aTimeForAdd, double aTimeForMin, double aTimeForRemoveMax);void AppController_initPerformanceMeasurement(AppController* _this);double AppController_timeForUnsortedArrayList_add(AppController* _this, UnsortedArrayList* aList, int aTestSize);double AppController_timeForUnsortedArrayList_min
(AppController* _this, UnsortedArrayList* aList, int aTestSize);
double AppController_timeForUnsortedArrayList_removeMax(AppController* _this, UnsortedArrayList* aList, int aTestSize);


double AppController_timeForSortedArrayList_add(AppController* _this, SortedArrayList* aList, int aTestSize);
double AppController_timeForSortedArrayList_min
(AppController* _this, SortedArrayList* aList, int aTestSize);
double AppController_timeForSortedArrayList_removeMax(AppController* _this, SortedArrayList* aList, int aTestSize);