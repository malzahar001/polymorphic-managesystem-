#include "Class_Worker.h"

Manager::Manager(int id, string name, int dId) {
	this->m_DeptId = dId;
	this->m_Id = id;
	this->m_Name = name;
}
//��ʾ������Ϣ
void Manager::showInfo() {
	cout << "ְ����ţ� " << this->m_Id
		<< "\tְ�������� " << this->m_Id
		<< "\t��λ�� " << this->getDeptName()
		<< "\t��λְ�� ����ϰ彻��������" << endl;
}

//��ȡ��λ����
string Manager::getDeptName() {
	return string("����");
}
