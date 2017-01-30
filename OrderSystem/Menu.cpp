#include"Menu.h"

Menu::Menu(string foodname,double price):FoodName(foodname),Price(price){}
string Menu::getFoodName()
{
	return FoodName;
}
double Menu::getPrice()
{
	return Price;
}

Order::Order(string personname,string phonenumber,string address,
			 string foodname,double price,int number,bool check):
			 PersonName(personname),PhoneNumber(phonenumber),Address(address),
			 Menu(foodname,price),Number(number),Checked(check),Canceled(false){}//储存订单，默认为未确认未删除

string Order::getPersonName()
{
	return PersonName;
}
string Order::getPhoneNumber()
{
	return PhoneNumber;
}
string Order::getAddress()
{
	return Address;
}
int Order::getNumber()
{
	return Number;
}
void Order::Check()//订单确认
{
	Checked=true;
}
bool Order::wasChecked()//返回订单是否被确认
{
	return Checked;
}
void Order::Cancel()//订单删除
{
	Canceled=true;
}
bool Order::wasCanceled()//返回订单是否被删除
{
	return Canceled;
}
