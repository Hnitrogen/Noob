#include <iostream>
#include "Employee.h"

using namespace std;

//����ʵ��--> ��Ĺ��캯��/���麯��

//���캯����ʵ��
Employee::Employee(string name,int id,int deptid)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = deptid;
}


void Employee::showInfo()
{
	cout << "Number: " << this->m_Id;
	cout << "    \tName: " << this->m_Name;

	cout << "    \tDepartment: " << this->getDeptName();
	cout << "\t  ��λְ��: ��ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}

