#pragma once
#include<iostream>
#include<string>
using namespace std;
//职工抽象类(不需要CPP定义文件)
class Class_Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptId;
};
//员工类
class Employee:public Class_Worker
{
public:
	//构造函数
	Employee(int id,string name,int dId);

	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};
//经理类
class Manager :public Class_Worker
{
public:
	//构造函数
	Manager(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};
//老板类
class Boss :public Class_Worker
{
public:
	//构造函数
	Boss(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};
