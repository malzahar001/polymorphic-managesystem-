#include "Class_Worker.h"

Boss::Boss(int id, string name, int dId) {
	this->m_DeptId = dId;
	this->m_Id = id;
	this->m_Name = name;
}
//��ʾ������Ϣ
void Boss::showInfo() {
	cout << "ְ����ţ� " << this->m_Id
		<< "\tְ�������� " << this->m_Id
		<< "\t��λ�� " << this->getDeptName()
		<< "\t��λְ�� ����˾��������" << endl;
}

//��ȡ��λ����
string Boss::getDeptName() {
	return string("�ϰ�");
}
