#include<iostream>
#include<fstream>
#include "Class_Management.h"
#include "Class_Worker.h"
using namespace std;

int main() {
	Class_Management CM;//���������
	int choice = 0;
	while (true) {
		CM.show_menu();//��ʾ�˵�
		cout << "����������ѡ��:" << endl;
		cin >> choice;
		//ѡ��˵�
		switch (choice)
		{
		case 0: //�˳�ϵͳ
			CM.exit_System();
			break;
		case 1: //���ְ��
			CM.add_Emp();
			break;
		case 2: //��ʾְ��
			CM.Show_Emp();
			break;
		case 3: //ɾ��ְ��
			CM.Del_Emp();
			break;
		case 4: //�޸�ְ��
			CM.Mod_Emp();
			break;
		case 5: //����ְ��
			CM.Find_Emp();
			break;
		case 6: //����ְ��
			CM.Sort_Emp();
			break;
		case 7: //����ļ�
			CM.clear_Emp();
			break;
		default:    //������Ч�����������Ȼ��������ʾ�˵���ѡ��˵�
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}