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
	
	
	//选项函数
	void Emp_add();
	void Emp_show();
	void Emp_del();
	void Emp_mod();
	void Emp_search();
	void Emp_sorted();
	void Emp_clean();

	~WorkerManager();

public:
	//辅助函数/属性:

	//职工人数
	int m_EmpNum;
	//职工数组指针
	Worker ** m_EmpAarry;	//这是一个 双指针
	//是指针 -->指向指针数组的指针 -->这个指针数组指向的是类外的(堆区)的对象
	
	//判断是否有职工表
	bool File_isEmpty ;
	//初始化员工
	void init_Emp();
	//保存到文档
	void save();
	//职工是否存在
	int  Emp_isexisit(int iid);

};

