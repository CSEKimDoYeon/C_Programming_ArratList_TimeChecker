#include "AppController.h"

int main(void)
{
	AppController* appController = AppController_new();
	// AppController ��ü ����.
	AppController_run(appController);
	// AppController ����.
	AppController_delete(appController);
	// AppController ����.
	system("pause");
	// �ܼ� ��� ���� ����.
	return 0;
}