
#include "Timer.h"
#include "UnsortedArrayList.h"

struct _UnsortedArrayList{
	int _capacity;
int _size;
Element* _elements;
}; // UnsortedArrayList ����ü ����

UnsortedArrayList* UnsortedArrayList_new(int givenCapacity)
{ //// UnsortedArrayList ��ü ����.
	UnsortedArrayList* _this = (UnsortedArrayList*)malloc(sizeof(UnsortedArrayList));
	_this->_capacity = givenCapacity;
	_this->_elements = NewVector(Element, _this->_capacity);
	_this->_size = 0; // �迭, �ִ�ũ�� �� �������� setting
	return _this;
}

void UnsortedArrayList_delete(UnsortedArrayList* _this)
{// UnsortedArrayList �Ҹ���.
	free(_this);
}

Boolean UnsortedArrayList_isEmpty(UnsortedArrayList* _this)
{ // UnsortedArrayList�� ����ִ��� �Ǻ�.
	if (_this->_size == 0)
		return TRUE;
	else
		return FALSE;
}

Boolean UnsortedArrayList_isFull(UnsortedArrayList* _this)
{ // UnsortedArrayList�� ���� �� �ִ��� �Ǻ�.
	if (_this->_size == _this->_capacity)
		return TRUE;
	else
		return FALSE;
}

Boolean UnsortedArrayList_add(UnsortedArrayList* _this, Element anElement)
{ // UnsortedArrayList�� anElement ���� �߰��ϴ� �Լ�.
	if (UnsortedArrayList_isFull(_this)) 
		return FALSE; // ���� �� ���� ��� �߰����� �ʴ´�.
	else {
		_this->_elements[_this->_size] = anElement;
		(_this->_size)++; // �߰��� �Ϸ�Ǹ� size�� +1 ó�� ���ش�.
		return TRUE;
	}
}

Element UnsortedArrayList_removeMax(UnsortedArrayList* _this)
{ // UnsortedArrayList�� �ִ� ���� �����ϴ� �Լ�.
	int maxPosition;
	Element max;
	maxPosition =
		UnsortedArrayList_maxPositionRecursively(_this, 0, _this->_size - 1);
	max = UnsortedArrayList_removeAt(_this, maxPosition);
	// �������� ����Լ��� ���Ͽ� ���ϰ� �� �ε����� �ش��ϴ� �ִ밪�� ��ȯ.
	return max;
}

int UnsortedArrayList_maxPositionRecursively(UnsortedArrayList* _this, int left, int right)
{ // UnsortedArrayList�� �ִ밪�� �ش��ϴ� index�� �˻��ϴ� ����Լ�.
	if (left == right) {
		// �������� size�� 1�� ��� 
		return left; 
	}
	else { 
		int mid = (left + right) / 2;
		// �¿� �ε����� ������ mid�� ����
		int maxPositionOfLeftPart = UnsortedArrayList_maxPositionRecursively(_this, left, mid);
		int maxPositionOfRightPart = UnsortedArrayList_maxPositionRecursively(_this, mid + 1, right);
		// �� ���� ��Ʈ�� ����� ����Լ� ����.
		if (_this->_elements[maxPositionOfLeftPart] >= _this->_elements[maxPositionOfRightPart]) {
			return maxPositionOfLeftPart;
		}
		else {
			return maxPositionOfRightPart;
		}
	}
}
Element UnsortedArrayList_removeAt(UnsortedArrayList* _this, int aPosition)
{ // UnsortedArrayList���� aPosition�� �ش�Ǵ� �� ����.
	// aPosition �� ���� �ݵ�� _this->_size�� ������ �۾ƾ� �Ѵ�
	Element removedElement = _this->_elements[aPosition];
	for (int i = (aPosition + 1); i < (_this->_size); i++) {
		_this->_elements[i - 1] = _this->_elements[i];
	}
	_this->_size--;
	return removedElement;
}
Element UnsortedArrayList_min(UnsortedArrayList* _this)
{ // UnsortedArrayList���� �ּҰ��� ã�� �Լ�.
	int minPosition;
	minPosition =
		UnsortedArrayList_minPositionRecursively(_this, 0, _this->_size - 1);
	// �ּҰ��� Position�� ����Լ��� ���Ͽ� ���Ѵ�.
	return _this->_elements[minPosition];
}

int UnsortedArrayList_minPositionRecursively(UnsortedArrayList* _this, int left, int right)
{ // UnsortedArrayList�� �ּҰ��� position�� ���ϴ� ����Լ�.
	if (left == right) { 
		return left; // �������� ũ�Ⱑ 1�� ���
	}
	else { 
		int mid = (left + right) / 2;
		// �� �� �ε����� �߰����� mid�� ����
		int minPositionOfLeftPart = UnsortedArrayList_minPositionRecursively(_this, left, mid);
		int minPositionOfRightPart = UnsortedArrayList_minPositionRecursively(_this, mid + 1, right);
		// �� ���� ��Ʈ�� ������ ����Լ� ����.
		if (_this->_elements[minPositionOfLeftPart] < _this->_elements[minPositionOfRightPart]) {
			return minPositionOfLeftPart;
		}
		else {
			return minPositionOfRightPart;
		}
	}
}