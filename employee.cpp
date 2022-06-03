#include <iostream>
#include "Employee.h"

using namespace std;

//类外实现--> 类的构造函数/纯虚函数

//构造函数的实现
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
	cout << "\t  岗位职责: 完成经理交付的任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}

