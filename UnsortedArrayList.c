
#include "Timer.h"
#include "UnsortedArrayList.h"

struct _UnsortedArrayList{
	int _capacity;
int _size;
Element* _elements;
}; // UnsortedArrayList 구조체 정의

UnsortedArrayList* UnsortedArrayList_new(int givenCapacity)
{ //// UnsortedArrayList 객체 생성.
	UnsortedArrayList* _this = (UnsortedArrayList*)malloc(sizeof(UnsortedArrayList));
	_this->_capacity = givenCapacity;
	_this->_elements = NewVector(Element, _this->_capacity);
	_this->_size = 0; // 배열, 최대크기 등 설정값을 setting
	return _this;
}

void UnsortedArrayList_delete(UnsortedArrayList* _this)
{// UnsortedArrayList 소멸자.
	free(_this);
}

Boolean UnsortedArrayList_isEmpty(UnsortedArrayList* _this)
{ // UnsortedArrayList가 비어있는지 판별.
	if (_this->_size == 0)
		return TRUE;
	else
		return FALSE;
}

Boolean UnsortedArrayList_isFull(UnsortedArrayList* _this)
{ // UnsortedArrayList가 가득 차 있는지 판별.
	if (_this->_size == _this->_capacity)
		return TRUE;
	else
		return FALSE;
}

Boolean UnsortedArrayList_add(UnsortedArrayList* _this, Element anElement)
{ // UnsortedArrayList에 anElement 값을 추가하는 함수.
	if (UnsortedArrayList_isFull(_this)) 
		return FALSE; // 가득 차 있을 경우 추가하지 않는다.
	else {
		_this->_elements[_this->_size] = anElement;
		(_this->_size)++; // 추가가 완료되면 size를 +1 처리 해준다.
		return TRUE;
	}
}

Element UnsortedArrayList_removeMax(UnsortedArrayList* _this)
{ // UnsortedArrayList의 최대 값을 삭제하는 함수.
	int maxPosition;
	Element max;
	maxPosition =
		UnsortedArrayList_maxPositionRecursively(_this, 0, _this->_size - 1);
	max = UnsortedArrayList_removeAt(_this, maxPosition);
	// 포지션을 재귀함수를 통하여 구하고 그 인덱스에 해당하는 최대값을 반환.
	return max;
}

int UnsortedArrayList_maxPositionRecursively(UnsortedArrayList* _this, int left, int right)
{ // UnsortedArrayList의 최대값에 해당하는 index를 검색하는 재귀함수.
	if (left == right) {
		// 데이터의 size가 1일 경우 
		return left; 
	}
	else { 
		int mid = (left + right) / 2;
		// 좌우 인덱스의 절반을 mid로 설정
		int maxPositionOfLeftPart = UnsortedArrayList_maxPositionRecursively(_this, left, mid);
		int maxPositionOfRightPart = UnsortedArrayList_maxPositionRecursively(_this, mid + 1, right);
		// 두 개의 파트로 나누어서 재귀함수 실행.
		if (_this->_elements[maxPositionOfLeftPart] >= _this->_elements[maxPositionOfRightPart]) {
			return maxPositionOfLeftPart;
		}
		else {
			return maxPositionOfRightPart;
		}
	}
}
Element UnsortedArrayList_removeAt(UnsortedArrayList* _this, int aPosition)
{ // UnsortedArrayList에서 aPosition에 해당되는 값 삭제.
	// aPosition 의 값은 반드시 _this->_size의 값보다 작아야 한다
	Element removedElement = _this->_elements[aPosition];
	for (int i = (aPosition + 1); i < (_this->_size); i++) {
		_this->_elements[i - 1] = _this->_elements[i];
	}
	_this->_size--;
	return removedElement;
}
Element UnsortedArrayList_min(UnsortedArrayList* _this)
{ // UnsortedArrayList에서 최소값을 찾는 함수.
	int minPosition;
	minPosition =
		UnsortedArrayList_minPositionRecursively(_this, 0, _this->_size - 1);
	// 최소값의 Position은 재귀함수를 통하여 구한다.
	return _this->_elements[minPosition];
}

int UnsortedArrayList_minPositionRecursively(UnsortedArrayList* _this, int left, int right)
{ // UnsortedArrayList의 최소값의 position을 구하는 재귀함수.
	if (left == right) { 
		return left; // 데이터의 크기가 1일 경우
	}
	else { 
		int mid = (left + right) / 2;
		// 좌 우 인덱스의 중간값을 mid로 설정
		int minPositionOfLeftPart = UnsortedArrayList_minPositionRecursively(_this, left, mid);
		int minPositionOfRightPart = UnsortedArrayList_minPositionRecursively(_this, mid + 1, right);
		// 두 개의 파트로 나누어 재귀함수 실행.
		if (_this->_elements[minPositionOfLeftPart] < _this->_elements[minPositionOfRightPart]) {
			return minPositionOfLeftPart;
		}
		else {
			return minPositionOfRightPart;
		}
	}
}