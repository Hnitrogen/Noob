#pragma once
#include <iostream>
#include "Worker.h"

class Boss :public Worker
{
public:
	Boss(string name, int id, int deptid);

	virtual void showInfo();


	virtual	string getDeptName();

};
