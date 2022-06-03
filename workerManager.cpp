#include <iostream>
#include <fstream>

#include "WorkerManager.h"
#define  FILENAME "empFile.txt"
using namespace std;

WorkerManager::WorkerManager()
{
	//初始化属性
	this->m_EmpNum = 0;
	this->m_EmpAarry = NULL;	
	
	//1. 文件为空
	ifstream ifs;
	ifs.open(FILENAME, ios::out);
	if (!ifs.is_open())
	{
		cout << "文件不存在!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpAarry = NULL;
		this->File_isEmpty = true;
		ifs.close();
		return;
	}
	//2. 文件存在,但是没有文本
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->File_isEmpty = true;
		this->m_EmpAarry = NULL;
		ifs.close();
		return ;
	}
	//3. 统计文件人数
	int num=this->get_EmpNum();
	//cout << "职工的人数是:" << num << endl;
	this->m_EmpNum = num;


	//根据职工数创建数组
	this->m_EmpAarry = new Worker * [this->m_EmpNum];
	//初始化职工
	init_Emp();

	////测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//   cout << "职工号： "    << this->m_EmpAarry[i]->m_Id
	//		<< " 职工姓名： " << this->m_EmpAarry[i]->m_Name
	//		<< " 部门编号： " << this->m_EmpAarry[i]->m_DeptId << endl;
	//}
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpAarry != NULL)
	{
		delete[] this->m_EmpAarry;
	}
}
//释放堆区数据,不过在这个项目里面没啥用
//(对象释放和程序结束同步)


void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次访问" << endl;
	system("pause");
	exit(0); //没啥意义= = --> 退出程序
}

void WorkerManager::Emp_add()
{
	
	cout << "请输入要添加的人数" << endl;
	int AddNum = 0; // 保存输入
	cin >> AddNum;

	//Again!!!
	if (AddNum > 0)//添加
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + AddNum;
		Worker** newSpace = new Worker * [newSize + 4]; // 储存指针的数组
		//为毛屁股+4就没有下面那个狗屁warning了


		//将原来数据拷贝到新空间

		if (this->m_EmpAarry != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpAarry[i]; //这警告啥玩意
			}
		}


		//添加数据
		string name;
		int id = 0, deptid = 0;

		for (int i = 0; i < AddNum; i++)
		{

			cout << "请输入第" << i +1<< "个职工的编号" << endl;
			cin >> id;

			cout << "请输入第" << i +1<< "个职工的姓名" << endl;
			cin >> name;

			cout << "请输入职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> deptid;


			Worker* worker = NULL;
			switch (deptid)
			{
			case 1:
				worker = new Employee(name, id, deptid);
				break;

			case 2:
				worker = new Manager(name, id, deptid);
				break;

			case 3:
				worker = new Boss(name, id, deptid);
				break;

			default:
				break;
			}
			
			//添加到数组里面去
			newSpace[this->m_EmpNum + i] = worker;
			//之前这里 initial i=1 --> 1,2让数组没从零开始
			
		}
		//释放原有空间
		delete[] this->m_EmpAarry;

		//更改新空间的指向
		this->m_EmpAarry = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;  // 之前忘记更新人数了= =

		this->save();		

		this->File_isEmpty = false;

			
		cout << "成功添加" << AddNum << "名职工" << endl;

		cout << "newSize :" << newSize << endl;


	}
	else
	{
		cout << "输入人数不合法" << endl;
	}
	

	system("pause");
	system("cls");
}


void WorkerManager::save()
{
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::out);


		for (int i = 0; i < this->m_EmpNum; i++)
		{
			ofs << this->m_EmpAarry[i]->m_Id << "    \t"
				<< this->m_EmpAarry[i]->m_Name << "     \t"
				<< this->m_EmpAarry[i]->m_DeptId<< endl;
			
			
		}

		ofs.close();
	}
}
int WorkerManager:: get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id, dId;
	string name;


	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}


void  WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id, dId,index=0;
	string name;

	

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* workers = NULL;
		if (dId == 1 )		workers = new	Employee(name, id, dId);
		else if(dId ==2 )	workers = new	Manager(name, id, dId);
		else if(dId == 3 )	workers = new	Boss(name, id, dId);
	
		this->m_EmpAarry[index] = workers;
		index++;
	}
	
}


void WorkerManager::Emp_show()
{
	if (this->File_isEmpty)
	{
		cout << "对应职工文档为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpAarry[i]->showInfo();
		}
	
		system("pause");
		system("cls");
	}
	
}

int  WorkerManager::Emp_isexisit(int iid)
{

	int index = -1; // 默认 置False
	
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpAarry[i]->m_Id == iid)
		{
			index = i;
			return index; // 用于返回索引
		}
	}
	
	return -1;
}

void WorkerManager::Emp_del()
{
	int index,id;
	
	if (this->File_isEmpty)
	{
		cout << "对应职工文档为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入你要删除的职工编号" << endl;
		cin >> id;
		
		index = this->Emp_isexisit(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum; i++)
			{
				this->m_EmpAarry[i] = this->m_EmpAarry[i + 1];
				//删除算法
			}
			this->m_EmpNum--;
			this->save(); // 用指针数组输入文件
			cout << "删除成功!" << endl;

			system("pause");
			system("cls");
		}
		else
		{
			cout << "查无此人,请重试!" << endl;
			system("pause");
			system("cls");
		}
		
	}
	
}

void WorkerManager::Emp_mod()
{
	int iid;
	cout << "请输入你要修改的职工编号!" << endl;
	cin >> iid;
	
	if (this->File_isEmpty)
	{
		cout << "对应职工文档为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int ret = this->Emp_isexisit(iid);
		
		if (ret != -1)
		{


			delete this->m_EmpAarry[ret];
			//删除被你手动开辟的动态空间

			string name;
			int id, deptid;

			cout << "请输入职工编号" << endl;
			cin >> id;
			cout << "请输入职工姓名" << endl;
			cin >> name;

			cout << "请输入职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> deptid;

			Worker* worker_tmp = NULL;

			switch (deptid)
			{
			case 1:
				worker_tmp = new Employee(name, id, deptid);
				break;
			case 2:
				worker_tmp = new Manager(name, id, deptid);
				break;
			case 3:
				worker_tmp = new Boss(name, id, deptid);
				break;
			default:
				break;
			}

			this->m_EmpAarry[ret] = worker_tmp; //储存指针的数组更新
			this->save();
			
			cout << "修改成功!" << endl;

			system("pause");
			system("cls");

		}
		else
		{
			cout << "查无此人!" << endl;
			system("pause");
			system("cls");
		}
	}
	
}

void WorkerManager::Emp_search()
{
	if (this->File_isEmpty)
	{
		cout << "职工文档为空" << endl;
		system("pause");
		system("cls");
	}	
	else
	{
		int select;

		cout << "请输入你的查找方式:" << endl;
		cout << "1. 按职工编号查找" << endl;
		cout << "2. 按职工姓名查找" << endl;

		cin >> select;
	
		if (select == 1)
		{
			int iid;
			cout << "请输入你要查找的职工编号" << endl;
			cin >> iid;
			int index = Emp_isexisit(iid);
			
			if (index!= -1 )
			{
				
				cout << "查找成功!" << endl;
				cout << "index:" << index << endl;
				
				this->m_EmpAarry[index]->showInfo();

				system("pause");
				system("cls");
			}
			else
			{
				cout << "查无此人!" << endl;

				system("pause");
				system("cls");
			}
		}

		//名字查找 --> 会出现重名
		else if (select == 2)
		{
			string iname;
			int flag = 0;
			cout << "请输入你要查找的职工姓名" << endl;
			cin >> iname;

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpAarry[i]->m_Name == iname)
				{
					this->m_EmpAarry[i]->showInfo();
					flag = 1;
						
				}
				
			}
			if (flag)
			{
				system("pause");
				system("cls");
			}
			else
			{
				cout << "查无此人!" << endl;
				system("pause");
				system("cls");
			}

			
		}
		else
		{
			system("cls");
		}
	}
}

void WorkerManager::Emp_clean()
{
	if (this->File_isEmpty)
	{
		cout << "职工文档为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择:" << endl;
		cout << "1. 清空" << endl;
		cout << "2. 返回" << endl;

		int select=0;
		cin >> select;

		if (select == 1)
		{
			//1. 删除文档
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();

			//手动释放堆区空间
			if (this->m_EmpAarry != NULL) //指向指针数组的指针不为空
			{


				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpAarry[i] != NULL)
					//指针数组中每个指针不为空
					{
						delete this->m_EmpAarry[i];
						//就释放这个动态变量(堆区)
					}
						
				}

				delete[] this->m_EmpAarry;
				//动态数组释放
				this->m_EmpAarry = NULL;
				//指向动态数组的指针置空

				this->m_EmpNum = 0;
				this->File_isEmpty = true;
			    
		    }
			cout << "清空成功!" << endl;
			system("pause");
			system("cls");
		
		}
		else
		{
			system("pause");
			system("cls");
		}
	
	}
}







void WorkerManager::Emp_sorted()
{
	if (this->File_isEmpty)
	{
		cout << "职工文档为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式" << endl;
		cout << "1. 按职工号升序排列" << endl;
		cout << "2. 按职工号降序排列" << endl; 

		int select = 0;
		cin >> select;
		
		//选择排序
		if (select == 1)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				int min = i;

				for (int j = i + 1; j < this->m_EmpNum; j++)
				{
					if (this->m_EmpAarry[min]->m_Id > this->m_EmpAarry[j]->m_Id)
					{
						min = j;
					}
				}
			
				if (i != min)
				{
					Worker* tmp = m_EmpAarry[i];
					m_EmpAarry[i] = m_EmpAarry[min];
					m_EmpAarry[min] = tmp;
				}

			
			
			
			}
			cout << "排序成功!" << endl;
			this->save();
			this->Emp_show();

		}
		else if (select == 2)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				int max = i;
				
				for (int j = i + 1; j < this->m_EmpNum; j++)
				{
					if (this->m_EmpAarry[max]->m_Id < this->m_EmpAarry[j]->m_Id)
					{
						max = j;
					}
				}
			
				if (max != i)
				{
					Worker* tmp = m_EmpAarry[i];
					m_EmpAarry[i] = m_EmpAarry[max];
					m_EmpAarry[max] = tmp;
				}
			
			}
			cout << "排序成功!" << endl;
			this->save();
			this->Emp_show();
		}
	}
}


