#include "Common.h"
typedef struct _UnsortedArrayList UnsortedArrayList;UnsortedArrayList* UnsortedArrayList_new(int givenCapacity);
void UnsortedArrayList_delete(UnsortedArrayList* _this);
Boolean UnsortedArrayList_isEmpty(UnsortedArrayList* _this);
Boolean UnsortedArrayList_isFull(UnsortedArrayList* _this);
Boolean UnsortedArrayList_add(UnsortedArrayList* _this, Element anElement);
Element UnsortedArrayList_removeMax(UnsortedArrayList* _this);int UnsortedArrayList_maxPositionRecursively(UnsortedArrayList* _this, int left, int right);Element UnsortedArrayList_removeAt(UnsortedArrayList* _this, int aPosition);
Element UnsortedArrayList_min(UnsortedArrayList* _this);
int UnsortedArrayList_minPositionRecursively(UnsortedArrayList* _this, int left, int right);