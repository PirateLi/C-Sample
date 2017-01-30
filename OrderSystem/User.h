#ifndef USER_H
#define USER_H
#include<vector>
#include<string>
#include"Menu.h"
using namespace std;

class User
{
public:
	virtual void modifyOrder(vector<Order*>)=0;//此纯虚函数在买家和卖家中有不同定义
};

class Seller:public User//卖家
{
public:
	Seller();
	void modifyOrder(vector<Order*>);
};

class Buyer:public User//买家
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
