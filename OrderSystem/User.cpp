#include"User.h"
#include<iostream>

Seller::Seller(){}
void Seller::modifyOrder(vector<Order*> order)//确认订单
{
	for(int i=0;i<order.size();i++)
		order[i]->Check();
}

Buyer::Buyer(){}
Buyer::Buyer(string personname,string phonenumber,string address)://用于储存买家信息：姓名、电话号码、地址
					PersonName(personname),PhoneNumber(phonenumber),Address(address){}
string Buyer::getPersonName()
{
	return PersonName;
}
string Buyer::getPhoneNumber()
{
	return PhoneNumber;
}
string Buyer::getAddress()
{
	return Address;
}

void Buyer::modifyOrder(vector<Order*> order)
{
	for(int i=0;i<order.size();i++)
		if(order[i]->wasChecked())//检查订单是否已被确认
		{
			cout<<"尊敬的客户 "<<order[i]->getPersonName()<<" 很抱歉，您想取消的第 "
				<<i+1<<" 张订单已被确认，取消订单失败。"<<endl;
			cout<<endl;
		}
		else
		{
			order[i]->Cancel();
			cout<<"尊敬的客户 "<<order[i]->getPersonName()<<" 您想取消的第 "
				<<i+1<<" 张订单已成功取消。"<<endl;
			cout<<endl;
		}
}
