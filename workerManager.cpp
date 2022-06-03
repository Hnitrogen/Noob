#include <iostream>
#include <fstream>

#include "WorkerManager.h"
#define  FILENAME "empFile.txt"
using namespace std;

WorkerManager::WorkerManager()
{
	//��ʼ������
	this->m_EmpNum = 0;
	this->m_EmpAarry = NULL;	
	
	//1. �ļ�Ϊ��
	ifstream ifs;
	ifs.open(FILENAME, ios::out);
	if (!ifs.is_open())
	{
		cout << "�ļ�������!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpAarry = NULL;
		this->File_isEmpty = true;
		ifs.close();
		return;
	}
	//2. �ļ�����,����û���ı�
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->File_isEmpty = true;
		this->m_EmpAarry = NULL;
		ifs.close();
		return ;
	}
	//3. ͳ���ļ�����
	int num=this->get_EmpNum();
	//cout << "ְ����������:" << num << endl;
	this->m_EmpNum = num;


	//����ְ������������
	this->m_EmpAarry = new Worker * [this->m_EmpNum];
	//��ʼ��ְ��
	init_Emp();

	////���Դ���
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//   cout << "ְ���ţ� "    << this->m_EmpAarry[i]->m_Id
	//		<< " ְ�������� " << this->m_EmpAarry[i]->m_Name
	//		<< " ���ű�ţ� " << this->m_EmpAarry[i]->m_DeptId << endl;
	//}
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpAarry != NULL)
	{
		delete[] this->m_EmpAarry;
	}
}
//�ͷŶ�������,�����������Ŀ����ûɶ��
//(�����ͷźͳ������ͬ��)


void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´η���" << endl;
	system("pause");
	exit(0); //ûɶ����= = --> �˳�����
}

void WorkerManager::Emp_add()
{
	
	cout << "������Ҫ��ӵ�����" << endl;
	int AddNum = 0; // ��������
	cin >> AddNum;

	//Again!!!
	if (AddNum > 0)//���
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + AddNum;
		Worker** newSpace = new Worker * [newSize + 4]; // ����ָ�������
		//Ϊëƨ��+4��û�������Ǹ���ƨwarning��


		//��ԭ�����ݿ������¿ռ�

		if (this->m_EmpAarry != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpAarry[i]; //�⾯��ɶ����
			}
		}


		//�������
		string name;
		int id = 0, deptid = 0;

		for (int i = 0; i < AddNum; i++)
		{

			cout << "�������" << i +1<< "��ְ���ı��" << endl;
			cin >> id;

			cout << "�������" << i +1<< "��ְ��������" << endl;
			cin >> name;

			cout << "������ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			
			//��ӵ���������ȥ
			newSpace[this->m_EmpNum + i] = worker;
			//֮ǰ���� initial i=1 --> 1,2������û���㿪ʼ
			
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpAarry;

		//�����¿ռ��ָ��
		this->m_EmpAarry = newSpace;

		//�����µĸ���
		this->m_EmpNum = newSize;  // ֮ǰ���Ǹ���������= =

		this->save();		

		this->File_isEmpty = false;

			
		cout << "�ɹ����" << AddNum << "��ְ��" << endl;

		cout << "newSize :" << newSize << endl;


	}
	else
	{
		cout << "�����������Ϸ�" << endl;
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
		//��¼����
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
		cout << "��Ӧְ���ĵ�Ϊ��!" << endl;
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

	int index = -1; // Ĭ�� ��False
	
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpAarry[i]->m_Id == iid)
		{
			index = i;
			return index; // ���ڷ�������
		}
	}
	
	return -1;
}

void WorkerManager::Emp_del()
{
	int index,id;
	
	if (this->File_isEmpty)
	{
		cout << "��Ӧְ���ĵ�Ϊ��!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������Ҫɾ����ְ�����" << endl;
		cin >> id;
		
		index = this->Emp_isexisit(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum; i++)
			{
				this->m_EmpAarry[i] = this->m_EmpAarry[i + 1];
				//ɾ���㷨
			}
			this->m_EmpNum--;
			this->save(); // ��ָ�����������ļ�
			cout << "ɾ���ɹ�!" << endl;

			system("pause");
			system("cls");
		}
		else
		{
			cout << "���޴���,������!" << endl;
			system("pause");
			system("cls");
		}
		
	}
	
}

void WorkerManager::Emp_mod()
{
	int iid;
	cout << "��������Ҫ�޸ĵ�ְ�����!" << endl;
	cin >> iid;
	
	if (this->File_isEmpty)
	{
		cout << "��Ӧְ���ĵ�Ϊ��!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		int ret = this->Emp_isexisit(iid);
		
		if (ret != -1)
		{


			delete this->m_EmpAarry[ret];
			//ɾ�������ֶ����ٵĶ�̬�ռ�

			string name;
			int id, deptid;

			cout << "������ְ�����" << endl;
			cin >> id;
			cout << "������ְ������" << endl;
			cin >> name;

			cout << "������ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

			this->m_EmpAarry[ret] = worker_tmp; //����ָ����������
			this->save();
			
			cout << "�޸ĳɹ�!" << endl;

			system("pause");
			system("cls");

		}
		else
		{
			cout << "���޴���!" << endl;
			system("pause");
			system("cls");
		}
	}
	
}

void WorkerManager::Emp_search()
{
	if (this->File_isEmpty)
	{
		cout << "ְ���ĵ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}	
	else
	{
		int select;

		cout << "��������Ĳ��ҷ�ʽ:" << endl;
		cout << "1. ��ְ����Ų���" << endl;
		cout << "2. ��ְ����������" << endl;

		cin >> select;
	
		if (select == 1)
		{
			int iid;
			cout << "��������Ҫ���ҵ�ְ�����" << endl;
			cin >> iid;
			int index = Emp_isexisit(iid);
			
			if (index!= -1 )
			{
				
				cout << "���ҳɹ�!" << endl;
				cout << "index:" << index << endl;
				
				this->m_EmpAarry[index]->showInfo();

				system("pause");
				system("cls");
			}
			else
			{
				cout << "���޴���!" << endl;

				system("pause");
				system("cls");
			}
		}

		//���ֲ��� --> ���������
		else if (select == 2)
		{
			string iname;
			int flag = 0;
			cout << "��������Ҫ���ҵ�ְ������" << endl;
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
				cout << "���޴���!" << endl;
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
		cout << "ְ���ĵ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ��:" << endl;
		cout << "1. ���" << endl;
		cout << "2. ����" << endl;

		int select=0;
		cin >> select;

		if (select == 1)
		{
			//1. ɾ���ĵ�
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();

			//�ֶ��ͷŶ����ռ�
			if (this->m_EmpAarry != NULL) //ָ��ָ�������ָ�벻Ϊ��
			{


				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpAarry[i] != NULL)
					//ָ��������ÿ��ָ�벻Ϊ��
					{
						delete this->m_EmpAarry[i];
						//���ͷ������̬����(����)
					}
						
				}

				delete[] this->m_EmpAarry;
				//��̬�����ͷ�
				this->m_EmpAarry = NULL;
				//ָ��̬�����ָ���ÿ�

				this->m_EmpNum = 0;
				this->File_isEmpty = true;
			    
		    }
			cout << "��ճɹ�!" << endl;
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
		cout << "ְ���ĵ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ķ�ʽ" << endl;
		cout << "1. ��ְ������������" << endl;
		cout << "2. ��ְ���Ž�������" << endl; 

		int select = 0;
		cin >> select;
		
		//ѡ������
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
			cout << "����ɹ�!" << endl;
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
			cout << "����ɹ�!" << endl;
			this->save();
			this->Emp_show();
		}
	}
}


