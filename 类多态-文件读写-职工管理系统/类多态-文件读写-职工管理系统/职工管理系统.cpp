#include<iostream>
#include<fstream>
#include "Class_Management.h"
#include "Class_Worker.h"
using namespace std;

int main() {
	Class_Management CM;//管理类对象
	int choice = 0;
	while (true) {
		CM.show_menu();//显示菜单
		cout << "请输入您的选择:" << endl;
		cin >> choice;
		//选择菜单
		switch (choice)
		{
		case 0: //退出系统
			CM.exit_System();
			break;
		case 1: //添加职工
			CM.add_Emp();
			break;
		case 2: //显示职工
			CM.Show_Emp();
			break;
		case 3: //删除职工
			CM.Del_Emp();
			break;
		case 4: //修改职工
			CM.Mod_Emp();
			break;
		case 5: //查找职工
			CM.Find_Emp();
			break;
		case 6: //排序职工
			CM.Sort_Emp();
			break;
		case 7: //清空文件
			CM.clear_Emp();
			break;
		default:    //输入无效数字则会清屏然后重新显示菜单和选择菜单
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}