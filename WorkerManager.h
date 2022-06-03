#pragma once
#include <iostream>
#include <fstream>
#define  FILENAME "empFile.txt"

#include "Worker.h"
#include "Employee.h"
#include "manager.h"
#include "Boss.h"
using namespace std;

class WorkerManager
{
public:
	
	int get_EmpNum();
	
	WorkerManager();
	
	void Show_Menu();

	void exitSystem();
	
	
	//ѡ���
	void Emp_add();
	void Emp_show();
	void Emp_del();
	void Emp_mod();
	void Emp_search();
	void Emp_sorted();
	void Emp_clean();

	~WorkerManager();

public:
	//��������/����:

	//ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker ** m_EmpAarry;	//����һ�� ˫ָ��
	//��ָ�� -->ָ��ָ�������ָ�� -->���ָ������ָ����������(����)�Ķ���
	
	//�ж��Ƿ���ְ����
	bool File_isEmpty ;
	//��ʼ��Ա��
	void init_Emp();
	//���浽�ĵ�
	void save();
	//ְ���Ƿ����
	int  Emp_isexisit(int iid);

};

