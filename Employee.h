#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;

class Employee : public Worker
{
public:	
	Employee(string name, int id, int deptid);
	
	virtual void showInfo();
	

	virtual	string getDeptName() ;

};