#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
	StudentMIS sysu;
	StudentBase* pBase;
	First* pFirst;
	Second* pSecond;
	StudentMIS* pMIS;

	pFirst=&sysu;
	pSecond=&sysu;
	pBase=&sysu;
	pMIS=&sysu;

	int n;
	while (1)
	{
		
		system("cls");
		cout<<"��ӭʹ��ѧ����Ϣ����ϵͳ����ѡ��Ȩ�ޣ�"<<endl;
		cout<<"1. ������"<<endl;
		cout<<"2. ����רҵ����Ա"<<endl;
		cout<<"3. ����רҵ����Ա"<<endl;
		cout<<"4. ѧλ��"<<endl;
		cout<<"0. �˳�ϵͳ"<<endl;
		cout<<"������: ";
		while(cin>>n &&( n<0 || n>4)) cout<<"����������������룺 ";
		if (n==1) pBase->selectOperation();
		if (n==2) pFirst->selectOperation();
		if (n==3) pSecond->selectOperation();
		if (n==4) pMIS->selectOperation();
		if (n==0) break;
	}
}

