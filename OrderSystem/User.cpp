#include"User.h"
#include<iostream>

Seller::Seller(){}
void Seller::modifyOrder(vector<Order*> order)//ȷ�϶���
{
	for(int i=0;i<order.size();i++)
		order[i]->Check();
}

Buyer::Buyer(){}
Buyer::Buyer(string personname,string phonenumber,string address)://���ڴ��������Ϣ���������绰���롢��ַ
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
		if(order[i]->wasChecked())//��鶩���Ƿ��ѱ�ȷ��
		{
			cout<<"�𾴵Ŀͻ� "<<order[i]->getPersonName()<<" �ܱ�Ǹ������ȡ���ĵ� "
				<<i+1<<" �Ŷ����ѱ�ȷ�ϣ�ȡ������ʧ�ܡ�"<<endl;
			cout<<endl;
		}
		else
		{
			order[i]->Cancel();
			cout<<"�𾴵Ŀͻ� "<<order[i]->getPersonName()<<" ����ȡ���ĵ� "
				<<i+1<<" �Ŷ����ѳɹ�ȡ����"<<endl;
			cout<<endl;
		}
}
