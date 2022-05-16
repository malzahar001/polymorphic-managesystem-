#pragma once
#include<iostream>
#include<string>
using namespace std;
//ְ��������(����ҪCPP�����ļ�)
class Class_Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//���ű��
	int m_DeptId;
};
//Ա����
class Employee:public Class_Worker
{
public:
	//���캯��
	Employee(int id,string name,int dId);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};
//������
class Manager :public Class_Worker
{
public:
	//���캯��
	Manager(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};
//�ϰ���
class Boss :public Class_Worker
{
public:
	//���캯��
	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};
