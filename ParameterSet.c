#include "ParameterSet.h"

struct _ParameterSet {
	int _minTestSize;
	int _intervalSize;
	int _numberOfTests;
}; ParameterSet* ParameterSet_new(void) { 
	ParameterSet* _this = (ParameterSet*)malloc(sizeof(ParameterSet));
	return _this;
} // ���ο� ParameterSet ����ü ����.

ParameterSet* ParameterSet_newWith (givenMinTestSize, givenIntervalSize, givenNumberOfTests)
// �ʱ�ȭ ���� �־����� ������
{
	ParameterSet* _this = (ParameterSet*)malloc(sizeof(ParameterSet));
	_this->_minTestSize = givenMinTestSize;
	_this->_intervalSize = givenIntervalSize;
	_this->_numberOfTests = givenNumberOfTests; // �Ű����� ���� ��ü�� ����.
	return _this;
}
void ParameterSet_delete(ParameterSet* _this) { // �Ҹ���
	free(_this);
}void ParameterSet_setMinTestSize(ParameterSet* _this, int newMinTestSize) {
	_this->_minTestSize = newMinTestSize;
	// ParameterSet ��ü�� �ּ� �׽�Ʈ ������ ����.
}
int ParameterSet_minTestSize(ParameterSet* _this) {
	return _this->_minTestSize;
	// ParameterSet ��ü�� �ּ� �׽�Ʈ ������ ��ȯ.
}
void ParameterSet_setIntervalSize(ParameterSet* _this, int newIntervalSize) {
	_this->_intervalSize = newIntervalSize;
	//ParameterSet ��ü�� ���͹� ������ ����.
}
int ParameterSet_intervalSize(ParameterSet* _this) {
	return _this->_intervalSize;
	//ParameterSet ��ü�� ���͹� ������ ��ȯ.
}
void ParameterSet_setNumberOfTests(ParameterSet* _this, int newNumberOfTests) {
	_this->_numberOfTests = newNumberOfTests;
	//ParameterSet ��ü�� �׽�Ʈ �� ����.
}
int ParameterSet_numberOfTests(ParameterSet* _this) {
	return _this->_numberOfTests;
	//ParameterSet ��ü�� �׽�Ʈ �� ��ȯ.
}
int ParameterSet_maxTestSize(ParameterSet* _this) {
	return (_this->_minTestSize + (_this->_intervalSize * (_this->_numberOfTests - 1)));
	//ParameterSet ��ü�� �ִ� �׽�Ʈ ũ�� ��ȯ.
}