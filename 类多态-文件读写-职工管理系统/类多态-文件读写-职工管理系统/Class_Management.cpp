#include "Class_Management.h"
//����������
Class_Management::Class_Management() {

	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	//������ܴ򿪣�˵��������
	if (!ifs.is_open()) {
		//cout << "�ļ�������" << endl;
		//��ʼ�����Ժ�
		//��¼����
		m_EmpNum = 0;
		//ְ������ָ��
		m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		m_FileIsEmpty= true;
		ifs.close();
		return;
	}
	//2���ļ�������û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;
		//������Ա������ָ�롢�ļ��Ƿ�Ϊ��
		m_EmpNum = 0;
		m_FileIsEmpty = true;
		m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//3���ļ��������м�¼
	else {
	/*	cout << "ְ������Ϊ�� " << get_EmpNum() << endl;*/
		m_EmpNum = get_EmpNum();
		m_EmpArray = new Class_Worker * [m_EmpNum];//��Ա������ָ���¿ռ�
		init_Emp();//��ʼ��Ա������
	/*	for (int i = 0; i < m_EmpNum; i++) {
			cout << "ְ���ţ�" << m_EmpArray[i]->m_Id
				<< " ְ�������� " << m_EmpArray[i]->m_Name
				<< " ���ű�ţ� " << m_EmpArray[i]->m_DeptId << endl;
		}*/
	}
};
Class_Management::~Class_Management() {
	if (m_EmpArray != NULL) {
		delete[] m_EmpArray; //���ڶ����Ŀռ��ڴ棬������ͷ�
	}
};
//��ʾ�˵�
void Class_Management::show_menu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//�˳��˵�
void Class_Management::exit_System() {
	cout << "��ӭ�´���ʹ��" << endl;
	system("pause");
	exit(0);
}
//���ְ��
void Class_Management::add_Emp() {
	//����ԭ��������vector���Ԫ�ص�ԭ�������¿ռ䣬���ɿռ�����ݴ��ߣ�Ȼ��ɾ���ɿռ�
	cout << "����������ְ�������� " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum <= 0)
		cout << "���ְ���������ݴ���" << endl;
	else {
		//�����¿��ٿռ�Ĵ�С
		int newSize = m_EmpNum + addNum;
		//�����¿ռ�,ÿ��Class_Worker*���һ��Ա��
		Class_Worker** newSpace = new Class_Worker*[newSize];
		//���ɿռ����ݸ��Ƶ��¿ռ�
		if (m_EmpArray != NULL) {
			for (int i = 0; i < m_EmpNum; i++)
				newSpace[i] = m_EmpArray[i];
		}
		//����������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			
			cout << "�����"<<i+1<<"����ְ����id" << endl;
			cin >> id;

			cout << "�����" << i +1<< "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���" << i +1<< "����ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			//�õ����ݺ󣬽��������뵽һ����ʱ��Ա��������Ȼ���ŵ�Ա��������
			Class_Worker* worker = NULL;
			switch (dSelect) {
			case 1: //��ͨԱ��
				worker = new Employee(id, name, 1);
				break;
			case 2: //����
				worker = new Manager(id, name, 2);
				break;
			case 3:  //�ϰ�
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[m_EmpNum + i] = worker;
		}
		//����Ա����¼�뵽�¿ռ�󣬿�ʼɾ���ɿռ䣬����ָ��ָ���¿ռ�
		delete[] m_EmpArray;
		m_EmpArray = newSpace;
		//����Ա������
		m_EmpNum = newSize;

		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		m_FileIsEmpty = false;//�ļ���Ϊ��
		//�������ݵ��ļ���
		this->save();
	}

	system("pause");
	system("cls");
}
void Class_Management::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//��ÿ��������д�뵽�ļ���
	for (int i = 0; i < m_EmpNum; i++) {
		ofs << m_EmpArray[i]->m_Id << " "
			<< m_EmpArray[i]->m_Name << " "
			<< m_EmpArray[i]->m_DeptId << endl;
	}
	//�ر��ļ�
	ofs.close();
}
int Class_Management::get_EmpNum(){
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	//��ʱ���Դ���ļ��е�ÿ��
	int id;
	string name;
	int dId;

	int num = 0;

	//ÿ����һ�оͼ�¼����
	while (ifs >> id && ifs >> name && ifs>>dId) {
	   //��¼����
		num++;
	}
	ifs.close();

	return num;
}
//��ȡ�ļ��е���Ϣ��Ȼ���Ա�����鸳ֵ
void Class_Management::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Class_Worker* worker = NULL;
		//���ݲ�ͬ�Ĳ���Id������ͬ����
		if (dId == 1)
			worker = new Employee(id, name, dId);
		else if (dId == 2)
			worker = new Manager(id, name, dId);
		else if(dId == 3)
			worker = new Boss(id, name, dId);
		m_EmpArray[index] = worker;//����ʱ�������Ա������
		index++;
	}
}
void Class_Management::Show_Emp() {
	//�ж��ļ��Ƿ�Ϊ��
	if (m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		//�ǿգ����̬�������Ա������Ϣ
		for (int i = 0; i < m_EmpNum; i++) {
			m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
int Class_Management::IsExist(int id) {
	int index = -1;
	//����Ա�����������Ҷ�Ӧid
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Id == id) {
			return i;
		}
	}
	return index;
}

void Class_Management::Del_Emp() {
	if (m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		cout << "ɾ��ʧ��" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ����id" << endl;
		int id;
		cin >> id;
		int ret = IsExist(id);
		if (ret < 0) {
			cout << "ְ��������" << endl;
			cout << "ɾ��ʧ��" << endl;
		}
		else {
			cout << "ְ������" << endl;

			//ɾ��ǰ���ͷ��ڴ棬��Ϊ����ͨ��Ԫ�����Ƶķ�ʽ��ɾ�����ڶ���
			//���ڴ���Ȼ���ڣ������ֻ��ְ��������һ��ɾ������ѵ�ַ��Ȼ
			//�ڸÿռ��У���ʱ���������Ա����ԭ�ռ�ᶯ�¿ռ䣬ԭ�ռ��
			//ɾ��Ԫ�ؿ��ܻᱻ���Զ��ڴ�й¶
			delete m_EmpArray[ret];
			m_EmpArray[ret] = NULL;

			if (id < m_EmpNum - 1) {
				for (int i = id; i < m_EmpNum - 1; i++)
					m_EmpArray[i] = m_EmpArray[i + 1];
				m_EmpNum--;
			}
			else m_EmpNum--;
			//���ɾ���󣬸���Ϊ0������Ϊ�ļ�Ϊ��
			if (m_EmpNum == 0)
				m_FileIsEmpty = true;
			cout << "ɾ���ɹ�" << endl;
			
			save();//���ļ�����
		}
	}
	system("pause");
	system("cls");
}
void Class_Management::Mod_Emp() {
	if (m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��! " << endl;
	else {
		cout << "�������޸�ְ���ı�ţ� " << endl;
		int id;
		cin >> id;
		int ret = IsExist(id);
		if (ret < 0) {
			cout << "ְ��������,�޸�ʧ�ܣ�" << endl;
		}
		else {
			cout << "ְ������" << endl;
			//ע�⣺�������ɾ����Ա����������µ�Ա����������ֻ�޸�ֵ
			//��Ϊ���Ա���ĵ�ַ�Ѿ��̶�ָ��ĳ������
			delete m_EmpArray[ret];
			int id;
			string name;
			int dept;

			cout << "��������id" << endl;
			cin >> id;

			cout << "������������" << endl;
			cin >> name;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//������ʱ��Ա��ӵ�����ԭ��λ����
			m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			save();
		}
	}
	system("pause");
	system("cls");
}
void Class_Management::Find_Emp() {
	if (m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��! " << endl;
	else {
		cout << "��ѡ��Ҫ���ҵķ�ʽ " << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int option;
		cin >> option;
		if (option == 1) {
			cout << "������Ҫ����ְ����id" << endl;
			int id;
			cin >> id;
			int ret = IsExist(id);
			if (ret < 0) {
				cout << "ְ��������,����ʧ�ܣ�" << endl;
			}
			else {
				cout << "ְ������," << endl;
				m_EmpArray[ret]->showInfo();
			}
		}
		else if (option == 2) {
			cout << "������Ҫ����ְ��������" << endl;
			string name;
			cin >> name;
			bool ret = false;
			//ѭ�������ܹ�ʵ�ֲ���ͬ����ְ��
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_Id
						<< " �ŵ���Ϣ���£�" << endl;
					m_EmpArray[i]->showInfo();
					ret = true;
				}
			}
			if (ret == false)
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else cout << "����ѡ���д�" << endl;
	}
	system("pause");
	system("cls");
}

//����ͽ�����Զ��庯��
bool cmp1(Class_Worker* a, Class_Worker* b) {
	return a->m_Id < b->m_Id;
}
bool cmp2(Class_Worker* a, Class_Worker* b) {
	return a->m_Id > b->m_Id;
}
void Class_Management::Sort_Emp() {
	if (m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��! " << endl;
	else{
		cout << "��ѡ������ķ�ʽ" << endl;
		cout << "1������" << endl;
		cout << "2������" << endl;

		int option;
		cin >> option;
		if (option == 1) {
			sort(m_EmpArray, m_EmpArray + m_EmpNum, cmp1);
		}
		else if (option == 2) {
			sort(m_EmpArray, m_EmpArray + m_EmpNum, cmp2);
		}
		else cout << "����ѡ���д�" << endl;
		cout << "����ɹ���" << endl;
		save();//�ļ�Ҫ����
	}
	system("pause");
	system("cls");
}
void Class_Management::clear_Emp() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		//��������ļ�����ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc); 
		ofs.close();

		if (m_EmpArray != NULL) {
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < m_EmpNum; i++) {
				delete m_EmpArray[i];
				m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] m_EmpArray;
			m_EmpArray = NULL;
			m_EmpNum = 0;
			m_FileIsEmpty = true;
		}

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}