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
		cout<<"欢迎使用学生信息管理系统，请选择权限："<<endl;
		cout<<"1. 招生办"<<endl;
		cout<<"2. 主修专业教务员"<<endl;
		cout<<"3. 副修专业教务员"<<endl;
		cout<<"4. 学位办"<<endl;
		cout<<"0. 退出系统"<<endl;
		cout<<"请输入: ";
		while(cin>>n &&( n<0 || n>4)) cout<<"输入错误，请重新输入： ";
		if (n==1) pBase->selectOperation();
		if (n==2) pFirst->selectOperation();
		if (n==3) pSecond->selectOperation();
		if (n==4) pMIS->selectOperation();
		if (n==0) break;
	}
}

