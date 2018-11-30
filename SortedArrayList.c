#include "SortedArrayList.h"

struct _SortedArrayList {
	int _capacity;
	int _size;
	Element* _elements;
}; // SortedArrayList 구조체 생성.

SortedArrayList* SortedArrayList_new(int givenCapacity) {
	SortedArrayList* _this = (SortedArrayList*)malloc(sizeof(SortedArrayList));
	_this->_capacity = givenCapacity;
	_this->_elements = NewVector(Element, _this->_capacity);
	_this->_size = 0;
	return _this;
	// SortedArrayList 생성.
}

void SortedArrayList_delete(SortedArrayList* _this) {
	free(_this);
	// SortedArrayList 삭제.
}

Boolean SortedArrayList_isEmpty(SortedArrayList* _this) {
	// SortedArrayList가 비어있는지 판별.
	if (_this->_size == 0)
		return TRUE;
	else
		return FALSE;
}

Boolean SortedArrayList_isFull(SortedArrayList* _this) {
	// SortedArrayList가 꽉차있는지 판별.
	if (_this->_size == _this->_capacity)
		return TRUE;
	else
		return FALSE;
}

Boolean SortedArrayList_add(SortedArrayList* _this, Element anElement) {
	// SortedArrayList에 anElement를 추가
	if (SortedArrayList_isFull(_this)) {
		return FALSE; // 꽉차있으면 넣지 않는다.
	}
	else {
		//제 1단계: 삽입할 위치를 결정한다.
		int positionForAdd = SortedArrayList_positionUsingBinarySearch(_this, anElement);
		//제 2단계: 찾아진 삽입 위치에 주어진 원소를 삽입한다.
		SortedArrayList_addAt(_this, anElement, positionForAdd);
		return TRUE;
	}

}

int SortedArrayList_positionUsingBinarySearch(SortedArrayList* _this, Element anElement) {
	// SortedArrayList에서 삽입할 위치를 찾는 함수.
	int left = 0;
	int right = _this->_size - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2; // mid는 배열 양 끝의 index의 중간이다.
		if (anElement == _this->_elements[mid]) {
			return mid;
		}
		else if (anElement < _this->_elements[mid]) {
			right = mid - 1;
		}
		else if (anElement > _this->_elements[mid]) {
			left = mid + 1;
		}
	}
	return left;
}

void SortedArrayList_addAt(SortedArrayList* _this, Element anElement, int aPosition) {
	// SortedArrayList의 지정된 position에 anElement를 삽입.
	for (int i = (_this->_size - 1); i > aPosition; i--) {
		_this->_elements[i + 1] = _this->_elements[i];
	}
	_this->_elements[aPosition] = anElement;
	(_this->_size)++;
	// 삽입이 완료되면 size를 +1 처리해준다.
}

Element SortedArrayList_min(SortedArrayList* _this) {
	// SortedArrayList의 최소값을 찾는 함수.
	int minPosition;
	minPosition = SortedArrayList_minPositionRecursively(_this, 0, _this->_size - 1);
	// 최소값은 재귀함수를 통하여 찾아낸다.
	return _this->_elements[minPosition];
}

int SortedArrayList_minPositionRecursively(SortedArrayList* _this, int left, int right) {
	if (left == right) {  // 데이터의 총 크기가 1이여서 좌, 우 인덱스가 같을경우.
		return left;
	}
	else { 
		int mid = (left + right) / 2; // 좌, 우 인덱스의 절반을 mid값으로 지정.
		int minPositionOfLeftPart = SortedArrayList_minPositionRecursively(_this, left, mid);
		int minPositionOfRightPart = SortedArrayList_minPositionRecursively(_this, mid + 1, right);
		// 2개의 파트로 나누어서 재귀함수를 돌린다.
		if (_this->_elements[minPositionOfLeftPart] < _this->_elements[minPositionOfRightPart]) {
			return minPositionOfLeftPart;
		}
		else {
			return minPositionOfRightPart;
		}
	}
}

Element SortedArrayList_removeMax(SortedArrayList* _this) {
	// SortedArrayList에서 최대값을 삭제.
	int maxPosition;
	Element max;
	maxPosition = SortedArrayList_maxPositionRecursively(_this, 0, _this->_size - 1);
	// 최대값의 포지션은 재귀함수를 통하여 구한다.
	max = SortedArrayList_removeAt(_this, maxPosition);
	return max; // 포지션에 해당하는 값인 최대값을 return.
}

int SortedArrayList_maxPositionRecursively(SortedArrayList* _this, int left, int right) {
	if (left == right) { // 데이터의 길이가 1이여서 좌우가 동일할 경우.
		return left;
	}
	else { 
		int mid = (left + right) / 2; // mid값은 좌우 인덱스의 중간값으로
		int maxPositionOfLeftPart = SortedArrayList_maxPositionRecursively(_this, left, mid);
		int maxPositionOfRightPart = SortedArrayList_maxPositionRecursively(_this, mid + 1, right);
		// 두개의 파트로 나누어서 재귀함수를 돌린다.
		if (_this->_elements[maxPositionOfLeftPart] >= _this->_elements[maxPositionOfRightPart]) {
			return maxPositionOfLeftPart;
		}
		else {
			return maxPositionOfRightPart;
		}
	}
}

Element SortedArrayList_removeAt(SortedArrayList* _this, int aPosition) {
	//aPosition의 값은 반드시 _this->_size의 값보다 작아야 한다.
	Element removedElement = _this->_elements[aPosition];
	for (int i = (aPosition + 1); i < (_this->_size); i++) {
		_this->_elements[i - 1] = _this->_elements[i];
	}
	_this->_size--; // element를 remove 했으므로 size를 -1 처리해준다.
	return removedElement;
}