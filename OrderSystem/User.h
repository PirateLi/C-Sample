#ifndef USER_H
#define USER_H
#include<vector>
#include<string>
#include"Menu.h"
using namespace std;

class User
{
public:
	virtual void modifyOrder(vector<Order*>)=0;//�˴��麯������Һ��������в�ͬ����
};

class Seller:public User//����
{
public:
	Seller();
	void modifyOrder(vector<Order*>);
};

class Buyer:public User//���
{
public:
	Buyer();
	Buyer(string,string,string);
	string getPersonName();
	string getPhoneNumber();
	string getAddress();
	void modifyOrder(vector<Order*>);
protected:
	string PersonName,PhoneNumber,Address;
};
#endif
