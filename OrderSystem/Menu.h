#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;

class Menu
{
public:
	Menu(string,double);//�˵�������ʽ�����ƺͼ۸�
	string getFoodName();
	double getPrice();
protected:
	string FoodName;
	double Price;
};

class Order:public Menu//��Ϊ���������˲˵��в�ʽ�����ƺͼ۸�
{
public:
	Order(string,string,string,string,double,int,bool);//���������������绰����ַ�����������Ͳ˵��еĲ�ʽ���ƺͼ۸�
	string getPersonName();
	string getPhoneNumber();
	string getAddress();
	int getNumber();
	void Check();
	bool wasChecked();
	void Cancel();
	bool wasCanceled();
protected:
	int Number;
	bool Checked,Canceled;
	string PersonName,PhoneNumber,Address;
};
#endif
