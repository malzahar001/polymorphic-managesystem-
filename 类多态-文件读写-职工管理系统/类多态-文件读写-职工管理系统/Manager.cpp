#include "Class_Worker.h"

Manager::Manager(int id, string name, int dId) {
	this->m_DeptId = dId;
	this->m_Id = id;
	this->m_Name = name;
}
//显示个人信息
void Manager::showInfo() {
	cout << "职工编号： " << this->m_Id
		<< "\t职工姓名： " << this->m_Id
		<< "\t岗位： " << this->getDeptName()
		<< "\t岗位职责： 完成老板交给的任务" << endl;
}

//获取岗位名称
string Manager::getDeptName() {
	return string("经理");
}
