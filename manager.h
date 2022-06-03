#pragma once
#include <iostream>
#include "Worker.h"

class Manager : public Worker
{
public:

	Manager(string name, int id, int deptid);

	virtual	void showInfo();
	
	virtual	string getDeptName();
};