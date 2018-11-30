#include "SortedArrayList.h"

struct _SortedArrayList {
	int _capacity;
	int _size;
	Element* _elements;
}; // SortedArrayList ����ü ����.

SortedArrayList* SortedArrayList_new(int givenCapacity) {
	SortedArrayList* _this = (SortedArrayList*)malloc(sizeof(SortedArrayList));
	_this->_capacity = givenCapacity;
	_this->_elements = NewVector(Element, _this->_capacity);
	_this->_size = 0;
	return _this;
	// SortedArrayList ����.
}

void SortedArrayList_delete(SortedArrayList* _this) {
	free(_this);
	// SortedArrayList ����.
}

Boolean SortedArrayList_isEmpty(SortedArrayList* _this) {
	// SortedArrayList�� ����ִ��� �Ǻ�.
	if (_this->_size == 0)
		return TRUE;
	else
		return FALSE;
}

Boolean SortedArrayList_isFull(SortedArrayList* _this) {
	// SortedArrayList�� �����ִ��� �Ǻ�.
	if (_this->_size == _this->_capacity)
		return TRUE;
	else
		return FALSE;
}

Boolean SortedArrayList_add(SortedArrayList* _this, Element anElement) {
	// SortedArrayList�� anElement�� �߰�
	if (SortedArrayList_isFull(_this)) {
		return FALSE; // ���������� ���� �ʴ´�.
	}
	else {
		//�� 1�ܰ�: ������ ��ġ�� �����Ѵ�.
		int positionForAdd = SortedArrayList_positionUsingBinarySearch(_this, anElement);
		//�� 2�ܰ�: ã���� ���� ��ġ�� �־��� ���Ҹ� �����Ѵ�.
		SortedArrayList_addAt(_this, anElement, positionForAdd);
		return TRUE;
	}

}

int SortedArrayList_positionUsingBinarySearch(SortedArrayList* _this, Element anElement) {
	// SortedArrayList���� ������ ��ġ�� ã�� �Լ�.
	int left = 0;
	int right = _this->_size - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2; // mid�� �迭 �� ���� index�� �߰��̴�.
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
	// SortedArrayList�� ������ position�� anElement�� ����.
	for (int i = (_this->_size - 1); i > aPosition; i--) {
		_this->_elements[i + 1] = _this->_elements[i];
	}
	_this->_elements[aPosition] = anElement;
	(_this->_size)++;
	// ������ �Ϸ�Ǹ� size�� +1 ó�����ش�.
}

Element SortedArrayList_min(SortedArrayList* _this) {
	// SortedArrayList�� �ּҰ��� ã�� �Լ�.
	int minPosition;
	minPosition = SortedArrayList_minPositionRecursively(_this, 0, _this->_size - 1);
	// �ּҰ��� ����Լ��� ���Ͽ� ã�Ƴ���.
	return _this->_elements[minPosition];
}

int SortedArrayList_minPositionRecursively(SortedArrayList* _this, int left, int right) {
	if (left == right) {  // �������� �� ũ�Ⱑ 1�̿��� ��, �� �ε����� �������.
		return left;
	}
	else { 
		int mid = (left + right) / 2; // ��, �� �ε����� ������ mid������ ����.
		int minPositionOfLeftPart = SortedArrayList_minPositionRecursively(_this, left, mid);
		int minPositionOfRightPart = SortedArrayList_minPositionRecursively(_this, mid + 1, right);
		// 2���� ��Ʈ�� ����� ����Լ��� ������.
		if (_this->_elements[minPositionOfLeftPart] < _this->_elements[minPositionOfRightPart]) {
			return minPositionOfLeftPart;
		}
		else {
			return minPositionOfRightPart;
		}
	}
}

Element SortedArrayList_removeMax(SortedArrayList* _this) {
	// SortedArrayList���� �ִ밪�� ����.
	int maxPosition;
	Element max;
	maxPosition = SortedArrayList_maxPositionRecursively(_this, 0, _this->_size - 1);
	// �ִ밪�� �������� ����Լ��� ���Ͽ� ���Ѵ�.
	max = SortedArrayList_removeAt(_this, maxPosition);
	return max; // �����ǿ� �ش��ϴ� ���� �ִ밪�� return.
}

int SortedArrayList_maxPositionRecursively(SortedArrayList* _this, int left, int right) {
	if (left == right) { // �������� ���̰� 1�̿��� �¿찡 ������ ���.
		return left;
	}
	else { 
		int mid = (left + right) / 2; // mid���� �¿� �ε����� �߰�������
		int maxPositionOfLeftPart = SortedArrayList_maxPositionRecursively(_this, left, mid);
		int maxPositionOfRightPart = SortedArrayList_maxPositionRecursively(_this, mid + 1, right);
		// �ΰ��� ��Ʈ�� ����� ����Լ��� ������.
		if (_this->_elements[maxPositionOfLeftPart] >= _this->_elements[maxPositionOfRightPart]) {
			return maxPositionOfLeftPart;
		}
		else {
			return maxPositionOfRightPart;
		}
	}
}

Element SortedArrayList_removeAt(SortedArrayList* _this, int aPosition) {
	//aPosition�� ���� �ݵ�� _this->_size�� ������ �۾ƾ� �Ѵ�.
	Element removedElement = _this->_elements[aPosition];
	for (int i = (aPosition + 1); i < (_this->_size); i++) {
		_this->_elements[i - 1] = _this->_elements[i];
	}
	_this->_size--; // element�� remove �����Ƿ� size�� -1 ó�����ش�.
	return removedElement;
}