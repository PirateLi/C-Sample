#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;

class Menu
{
public:
	Menu(string,double);//菜单包括菜式的名称和价格
	string getFoodName();
	double getPrice();
protected:
	string FoodName;
	double Price;
};

class Order:public Menu//因为订单包括了菜单中菜式的名称和价格
{
public:
	Order(string,string,string,string,double,int,bool);//订单包括姓名、电话、地址、订餐数量和菜单中的菜式名称和价格
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
