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
	//����������
	Class_Management();
	~Class_Management();

	void show_menu();//��ʾ�˵�
	void exit_System();//�˳��˵�
	void add_Emp();//���ְ��
	void save();//�����ļ�
	int get_EmpNum();//��ȡ�ļ�����������
	void init_Emp();//��ʼ��Ա������
	void Show_Emp();//��ʾְ��
	void Del_Emp();//ɾ��ְ��
	int IsExist(int id);//�ж�ְ���Ƿ���ڣ������򷵻��±�λ�ã����򷵻�-1
	void Mod_Emp();//�޸�ְ����Ϣ
	void Find_Emp();//����ְ��
	void Sort_Emp();//����Ա��
	void clear_Emp();//���Ա��
public:
	int m_EmpNum;//��ǰԱ������
	Class_Worker** m_EmpArray;//Ա������(Worker*��)��ָ��
	bool m_FileIsEmpty;//��־�ļ��Ƿ�Ϊ��
};

