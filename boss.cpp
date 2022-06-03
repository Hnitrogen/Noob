#include <iostream>
#include "Boss.h"

Boss::Boss(string name, int id, int deptid)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = deptid;
}

void Boss:: showInfo()
{
	cout << "Number: " << this->m_Id;
	cout << "    \tName: " << this->m_Name;

	cout << "    \tDepartment: " << this->getDeptName();
	cout << "\t  岗位职责: 管理公司所有事务" << endl;
}

string Boss::getDeptName()
{
	return string("总裁");
}
