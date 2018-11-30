#include "AppController.h"

int main(void)
{
	AppController* appController = AppController_new();
	// AppController 객체 생성.
	AppController_run(appController);
	// AppController 실행.
	AppController_delete(appController);
	// AppController 삭제.
	system("pause");
	// 콘솔 즉시 종료 방지.
	return 0;
}