#include <iostream>
#include "manager.h"

Manager :: Manager(string name, int id, int deptid)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = deptid;
};

void Manager::showInfo()
{
	cout << "Number: " << this->m_Id;
	cout << "    \tName: " << this->m_Name;

	cout << "    \tDepartment: " << this->getDeptName();
	cout << "\t  岗位职责: 完成老板交给的任务,并下发任务给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}
