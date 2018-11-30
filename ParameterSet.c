#include "ParameterSet.h"

struct _ParameterSet {
	int _minTestSize;
	int _intervalSize;
	int _numberOfTests;
}; ParameterSet* ParameterSet_new(void) { 
	ParameterSet* _this = (ParameterSet*)malloc(sizeof(ParameterSet));
	return _this;
} // 새로운 ParameterSet 구조체 생성.

ParameterSet* ParameterSet_newWith (givenMinTestSize, givenIntervalSize, givenNumberOfTests)
// 초기화 값이 주어지는 생성자
{
	ParameterSet* _this = (ParameterSet*)malloc(sizeof(ParameterSet));
	_this->_minTestSize = givenMinTestSize;
	_this->_intervalSize = givenIntervalSize;
	_this->_numberOfTests = givenNumberOfTests; // 매개변수 값을 객체에 저장.
	return _this;
}
void ParameterSet_delete(ParameterSet* _this) { // 소멸자
	free(_this);
}void ParameterSet_setMinTestSize(ParameterSet* _this, int newMinTestSize) {
	_this->_minTestSize = newMinTestSize;
	// ParameterSet 객체에 최소 테스트 사이즈 설정.
}
int ParameterSet_minTestSize(ParameterSet* _this) {
	return _this->_minTestSize;
	// ParameterSet 객체의 최소 테스트 사이즈 반환.
}
void ParameterSet_setIntervalSize(ParameterSet* _this, int newIntervalSize) {
	_this->_intervalSize = newIntervalSize;
	//ParameterSet 객체에 인터벌 사이즈 설정.
}
int ParameterSet_intervalSize(ParameterSet* _this) {
	return _this->_intervalSize;
	//ParameterSet 객체의 인터벌 사이즈 반환.
}
void ParameterSet_setNumberOfTests(ParameterSet* _this, int newNumberOfTests) {
	_this->_numberOfTests = newNumberOfTests;
	//ParameterSet 객체에 테스트 수 설정.
}
int ParameterSet_numberOfTests(ParameterSet* _this) {
	return _this->_numberOfTests;
	//ParameterSet 객체의 테스트 수 반환.
}
int ParameterSet_maxTestSize(ParameterSet* _this) {
	return (_this->_minTestSize + (_this->_intervalSize * (_this->_numberOfTests - 1)));
	//ParameterSet 객체의 최대 테스트 크기 반환.
}