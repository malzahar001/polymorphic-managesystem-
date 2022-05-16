#pragma once
#include<iostream>
#include"Class_Worker.h"
#include<fstream>
#include<algorithm>
using namespace std;
#define FILENAME "EMP.txt" 
class Class_Management
{
public:
	//构造与析构
	Class_Management();
	~Class_Management();

	void show_menu();//显示菜单
	void exit_System();//退出菜单
	void add_Emp();//添加职工
	void save();//保存文件
	int get_EmpNum();//获取文件中已有人数
	void init_Emp();//初始化员工数组
	void Show_Emp();//显示职工
	void Del_Emp();//删除职工
	int IsExist(int id);//判断职工是否存在，存在则返回下标位置，否则返回-1
	void Mod_Emp();//修改职工信息
	void Find_Emp();//查找职工
	void Sort_Emp();//排序员工
	void clear_Emp();//清空员工
public:
	int m_EmpNum;//当前员工人数
	Class_Worker** m_EmpArray;//员工数组(Worker*型)的指针
	bool m_FileIsEmpty;//标志文件是否为空
};

