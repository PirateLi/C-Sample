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
			 Menu(foodname,price),Number(number),Checked(check),Canceled(false){}//���涩����Ĭ��Ϊδȷ��δɾ��

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
void Order::Check()//����ȷ��
{
	Checked=true;
}
bool Order::wasChecked()//���ض����Ƿ�ȷ��
{
	return Checked;
}
void Order::Cancel()//����ɾ��
{
	Canceled=true;
}
bool Order::wasCanceled()//���ض����Ƿ�ɾ��
{
	return Canceled;
}
