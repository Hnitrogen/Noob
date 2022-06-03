#include <iostream>
#include "WorkerManager.h"

#include "Worker.h"
#include "Employee.h"
#include "manager.h"
#include "Boss.h"
using namespace std;

//程序入口
int main() {

	WorkerManager wm;
	int choice = 0;
	

	
	while (true)
	{
		//展示菜单
		wm.Show_Menu();
		cout << "请输入您的选择:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0: //退出系统
			wm.exitSystem();
			break;
		
		case 1: //添加职工	
			wm.Emp_add();
			break;
		
		case 2: //显示职工
			wm.Emp_show();
			break;
		
		case 3: //删除职工
			wm.Emp_del();
			break;
		
		case 4: //修改职工
			wm.Emp_mod();
			break;
		
		case 5: //查找职工
			wm.Emp_search();
			break;
		
		case 6: //排序职工
			wm.Emp_sorted();
			break;
		
		case 7: //清空文件
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