#include <iostream>
#include "WorkerManager.h"

#include "Worker.h"
#include "Employee.h"
#include "manager.h"
#include "Boss.h"
using namespace std;

//�������
int main() {

	WorkerManager wm;
	int choice = 0;
	

	
	while (true)
	{
		//չʾ�˵�
		wm.Show_Menu();
		cout << "����������ѡ��:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: //�˳�ϵͳ
			wm.exitSystem();
			break;
		
		case 1: //���ְ��	
			wm.Emp_add();
			break;
		
		case 2: //��ʾְ��
			wm.Emp_show();
			break;
		
		case 3: //ɾ��ְ��
			wm.Emp_del();
			break;
		
		case 4: //�޸�ְ��
			wm.Emp_mod();
			break;
		
		case 5: //����ְ��
			wm.Emp_search();
			break;
		
		case 6: //����ְ��
			wm.Emp_sorted();
			break;
		
		case 7: //����ļ�
			wm.Emp_clean();
			break;
		
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}