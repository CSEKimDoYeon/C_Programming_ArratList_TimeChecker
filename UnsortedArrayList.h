#include "Common.h"

void UnsortedArrayList_delete(UnsortedArrayList* _this);
Boolean UnsortedArrayList_isEmpty(UnsortedArrayList* _this);
Boolean UnsortedArrayList_isFull(UnsortedArrayList* _this);
Boolean UnsortedArrayList_add(UnsortedArrayList* _this, Element anElement);
Element UnsortedArrayList_removeMax(UnsortedArrayList* _this);
Element UnsortedArrayList_min(UnsortedArrayList* _this);
int UnsortedArrayList_minPositionRecursively(UnsortedArrayList* _this, int left, int right);