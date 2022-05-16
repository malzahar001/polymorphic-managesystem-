#include "Class_Management.h"
//构造与析构
Class_Management::Class_Management() {

	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	//如果不能打开，说明不存在
	if (!ifs.is_open()) {
		//cout << "文件不存在" << endl;
		//初始化属性和
		//记录人数
		m_EmpNum = 0;
		//职工数组指针
		m_EmpArray = NULL;
		//初始化文件是否为空
		m_FileIsEmpty= true;
		ifs.close();
		return;
	}
	//2、文件存在且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空！" << endl;
		//人数、员工数组指针、文件是否为空
		m_EmpNum = 0;
		m_FileIsEmpty = true;
		m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//3、文件存在且有记录
	else {
	/*	cout << "职工个数为： " << get_EmpNum() << endl;*/
		m_EmpNum = get_EmpNum();
		m_EmpArray = new Class_Worker * [m_EmpNum];//给员工数组指向新空间
		init_Emp();//初始化员工数组
	/*	for (int i = 0; i < m_EmpNum; i++) {
			cout << "职工号：" << m_EmpArray[i]->m_Id
				<< " 职工姓名： " << m_EmpArray[i]->m_Name
				<< " 部门编号： " << m_EmpArray[i]->m_DeptId << endl;
		}*/
	}
};
Class_Management::~Class_Management() {
	if (m_EmpArray != NULL) {
		delete[] m_EmpArray; //有在堆区的空间内存，则必须释放
	}
};
//显示菜单
void Class_Management::show_menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//退出菜单
void Class_Management::exit_System() {
	cout << "欢迎下次再使用" << endl;
	system("pause");
	exit(0);
}
//添加职工
void Class_Management::add_Emp() {
	//具体原理：类似于vector添加元素的原理，开辟新空间，将旧空间的数据带走，然后删除旧空间
	cout << "请输入增加职工数量： " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum <= 0)
		cout << "添加职工数量数据错误" << endl;
	else {
		//计算新开辟空间的大小
		int newSize = m_EmpNum + addNum;
		//开辟新空间,每个Class_Worker*存放一个员工
		Class_Worker** newSpace = new Class_Worker*[newSize];
		//将旧空间数据复制到新空间
		if (m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++)
				newSpace[i] = m_EmpArray[i];
		}
		//输入新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			
			cout << "输入第"<<i+1<<"个新职工的id" << endl;
			cin >> id;

			cout << "输入第" << i +1<< "个新职工的姓名" << endl;
			cin >> name;

			cout << "请选择第" << i +1<< "个新职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			//得到数据后，将数据载入到一个临时的员工变量，然后存放到员工数组中
			Class_Worker* worker = NULL;
			switch (dSelect) {
			case 1: //普通员工
				worker = new Employee(id, name, 1);
				break;
			case 2: //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[m_EmpNum + i] = worker;
		}
		//所有员工都录入到新空间后，开始删除旧空间，并将指针指向新空间
		delete[] m_EmpArray;
		m_EmpArray = newSpace;
		//更新员工个数
		m_EmpNum = newSize;

		cout << "成功添加" << addNum << "名新职工！" << endl;
		m_FileIsEmpty = false;//文件不为空
		//保存数据到文件中
		this->save();
	}

	system("pause");
	system("cls");
}
void Class_Management::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//将每个人数据写入到文件中
	for (int i = 0; i < m_EmpNum; i++) {
		ofs << m_EmpArray[i]->m_Id << " "
			<< m_EmpArray[i]->m_Name << " "
			<< m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}
int Class_Management::get_EmpNum(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//临时属性存放文件中的每行
	int id;
	string name;
	int dId;

	int num = 0;

	//每输入一行就记录人数
	while (ifs >> id && ifs >> name && ifs>>dId) {
	   //记录人数
		num++;
	}
	ifs.close();

	return num;
}
//读取文件中的信息，然后给员工数组赋值
void Class_Management::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Class_Worker* worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)
			worker = new Employee(id, name, dId);
		else if (dId == 2)
			worker = new Manager(id, name, dId);
		else if(dId == 3)
			worker = new Boss(id, name, dId);
		m_EmpArray[index] = worker;//将临时对象存入员工数组
		index++;
	}
}
void Class_Management::Show_Emp() {
	//判断文件是否为空
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		//非空，则多态输出各个员工的信息
		for (int i = 0; i < m_EmpNum; i++) {
			m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
int Class_Management::IsExist(int id) {
	int index = -1;
	//遍历员工数组来查找对应id
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Id == id) {
			return i;
		}
	}
	return index;
}

void Class_Management::Del_Emp() {
	if (m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
		cout << "删除失败" << endl;
	}
	else {
		cout << "请输入想要删除的职工的id" << endl;
		int id;
		cin >> id;
		int ret = IsExist(id);
		if (ret < 0) {
			cout << "职工不存在" << endl;
			cout << "删除失败" << endl;
		}
		else {
			cout << "职工存在" << endl;

			//删除前先释放内存，因为若是通过元素左移的方式来删除，在堆中
			//的内存依然存在，而如果只是职工个数减一来删除，则堆地址依然
			//于该空间中，这时如果插入新员工，原空间搬动新空间，原空间的
			//删除元素可能会被忽略而内存泄露
			delete m_EmpArray[ret];
			m_EmpArray[ret] = NULL;

			if (id < m_EmpNum - 1) {
				for (int i = id; i < m_EmpNum - 1; i++)
					m_EmpArray[i] = m_EmpArray[i + 1];
				m_EmpNum--;
			}
			else m_EmpNum--;
			//如果删除后，个数为0，则认为文件为空
			if (m_EmpNum == 0)
				m_FileIsEmpty = true;
			cout << "删除成功" << endl;
			
			save();//将文件保存
		}
	}
	system("pause");
	system("cls");
}
void Class_Management::Mod_Emp() {
	if (m_FileIsEmpty)
		cout << "文件不存在或记录为空! " << endl;
	else {
		cout << "请输入修改职工的编号： " << endl;
		int id;
		cin >> id;
		int ret = IsExist(id);
		if (ret < 0) {
			cout << "职工不存在,修改失败！" << endl;
		}
		else {
			cout << "职工存在" << endl;
			//注意：这里必须删除该员工，再添加新的员工，而不是只修改值
			//因为这个员工的地址已经固定指向某个子类
			delete m_EmpArray[ret];
			int id;
			string name;
			int dept;

			cout << "请输入新id" << endl;
			cin >> id;

			cout << "请输入新姓名" << endl;
			cin >> name;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dept;
			
			Class_Worker* worker = NULL;
			switch (dept) {
			case 1:worker = new Employee(id,name,dept);
				break;
			case 2:worker = new Manager(id, name, dept);
				break;
			case 3:worker = new Boss(id, name, dept);
				break;
			default:break;
			}
			//将该临时成员添加到数组原来位置中
			m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			save();
		}
	}
	system("pause");
	system("cls");
}
void Class_Management::Find_Emp() {
	if (m_FileIsEmpty)
		cout << "文件不存在或记录为空! " << endl;
	else {
		cout << "请选择要查找的方式 " << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int option;
		cin >> option;
		if (option == 1) {
			cout << "请输入要查找职工的id" << endl;
			int id;
			cin >> id;
			int ret = IsExist(id);
			if (ret < 0) {
				cout << "职工不存在,查找失败！" << endl;
			}
			else {
				cout << "职工存在," << endl;
				m_EmpArray[ret]->showInfo();
			}
		}
		else if (option == 2) {
			cout << "请输入要查找职工的姓名" << endl;
			string name;
			cin >> name;
			bool ret = false;
			//循环查找能够实现查找同名的职工
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_Id
						<< " 号的信息如下：" << endl;
					m_EmpArray[i]->showInfo();
					ret = true;
				}
			}
			if (ret == false)
				cout << "查找失败，查无此人" << endl;
		}
		else cout << "输入选项有错！" << endl;
	}
	system("pause");
	system("cls");
}

//升序和降序的自定义函数
bool cmp1(Class_Worker* a, Class_Worker* b) {
	return a->m_Id < b->m_Id;
}
bool cmp2(Class_Worker* a, Class_Worker* b) {
	return a->m_Id > b->m_Id;
}
void Class_Management::Sort_Emp() {
	if (m_FileIsEmpty)
		cout << "文件不存在或记录为空! " << endl;
	else{
		cout << "请选择排序的方式" << endl;
		cout << "1、升序" << endl;
		cout << "2、降序" << endl;

		int option;
		cin >> option;
		if (option == 1) {
			sort(m_EmpArray, m_EmpArray + m_EmpNum, cmp1);
		}
		else if (option == 2) {
			sort(m_EmpArray, m_EmpArray + m_EmpNum, cmp2);
		}
		else cout << "输入选项有错！" << endl;
		cout << "排序成功！" << endl;
		save();//文件要保存
	}
	system("pause");
	system("cls");
}
void Class_Management::clear_Emp() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		//如果存在文件，则删除文件后重新创建
		ofstream ofs(FILENAME, ios::trunc); 
		ofs.close();

		if (m_EmpArray != NULL) {
			//删除堆区的每个职工对象
			for (int i = 0; i < m_EmpNum; i++) {
				delete m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] m_EmpArray;
			m_EmpArray = NULL;
			m_EmpNum = 0;
			m_FileIsEmpty = true;
		}

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}