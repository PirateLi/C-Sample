#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include"User.h"
using namespace std;

vector<Menu> menulist;//��������ͱ���˵���Ϣ
vector<Order> orderlist;//��������ͱ��涩����Ϣ
Buyer *buyer;//1.������ʱ�����û���Ϣ�¶���ʱ���浽orderlist�� 2.���ڴ��ݵ�Buyer�е�modifyOrder(vector<Order*>

void loadmenulist()//����˵�
{
	int menunum;//�ļ���ͷ�Ĳ˵���
	fstream menuin;
	menuin.open("menu.txt",ios::in);

	menuin>>menunum;
	string foodname;
	double price;
	for(int i=0;i<menunum;i++)
	{
		menuin>>foodname>>price;
		menulist.push_back(Menu(foodname,price)); 
	}
	menuin.close();
}

void loadorderlist()//���붩��
{
	int ordernum;//�ļ���ͷ�Ķ�����
	fstream orderin;
	orderin.open("order.txt",ios::in);

	orderin>>ordernum;
	string personname,phonenumber,address,foodname;
	int number;
	double price;
	bool check;
	for(int i=0;i<ordernum;i++)
	{
		orderin>>personname>>phonenumber
			>>address>>foodname>>price>>number>>check;
		orderlist.push_back(Order(personname,
			phonenumber,address,foodname,price,number,check));
	}
	orderin.close();
}

void save()//����˵��붩��
{
	fstream menuout;
	menuout.open("menu.txt",ios::out);	 
	menuout<<menulist.size()<<endl;
	for(int i=0;i<menulist.size();i++)
	{
		menuout<<menulist[i].getFoodName()<<" "<<menulist[i].getPrice()<<endl;
	}
	menuout.close();
	 
	fstream orderout;
	orderout.open("order.txt",ios::out);
	orderout<<orderlist.size()<<endl;
	for(int i=0;i<orderlist.size();i++)
	{
		orderout<<orderlist[i].getPersonName()<<" ";
		orderout<<orderlist[i].getPhoneNumber()<<" ";
		orderout<<orderlist[i].getAddress()<<endl;
		orderout<<orderlist[i].getFoodName()<<" ";
		orderout<<orderlist[i].getPrice()<<" ";
		orderout<<orderlist[i].getNumber()<<endl;
		orderout<<orderlist[i].wasChecked()<<endl;
	}
	orderout.close();
}

bool checkin(string str)//���ͻ������Ƿ��з�����
{
	for(int i=0;i<str.size();i++)
		if(str[i]<'0'||str[i]>'9')
			return false;
	return true;
}

int transform(string str)//�ַ���ת��Ϊ����
{
	int n=0;
	for(int i=0;i<str.size();i++)
	{
		n=n*10;
		n+=str[i]-'0';
	}
	return n;
}

void displaymenu()//չʾ�˵�
{
	cout<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	if(menulist.empty())//��û�в˵�
		cout<<"�Բ�������δ��Ӳ˵���Ϣ��"<<endl;
	else
		for(int i=0;i<menulist.size();i++)//��ӡ�˵�
			cout<<left<<"# "<<setw(3)<<i+1<<": "<<setw(25)<<menulist[i].getFoodName()
				<<" ��"<<setw(7)<<fixed<<setprecision(2)<<menulist[i].getPrice()<<endl;
}

void adddish()//���Ӳ�ʽ
{
	system("cls");
	displaymenu();//��ӡ�˵�
	cout<<endl;
	string name;
	double price;
	cout<<"�������²�ʽ���ƣ�12�������ڣ�,����0���أ�"<<endl;
	cin>>name;
	if(name[0]!='0')
	{
		cout<<"�������²�ʽ�۸�"<<endl;
		cin>>price;
		menulist.push_back(Menu(name,price));//�����²�ʽ
		system("cls");
		cout<<endl;
		cout<<"����²�ʽ"<<left<<setw(25)<<name
				  <<" ��"<<setw(7)<<fixed<<setprecision(2)<<price<<"�ɹ���"<<endl;
		cout<<"��Ӳ�ʽ����������";
		cout<<endl;
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"��Ӳ�ʽ����������";
		cout<<endl;
	}
}

void deletedish()//ɾ����ʽ
{
	displaymenu();//��ӡ�˵�
	cout<<endl;
	cout<<"������Ҫɾ���Ĳ�ʽ��ţ�����0����"<<endl; 
	string str;//��ֹ������������֣���string���
	cin>>str;

	//�ж������Ƿ�Ϸ�
	bool bcheck=checkin(str);//���з����ַ���false
	while(!bcheck)//bcheck=false����������
	{
		cout<<endl;
		cout<<"�����������������Ҫɾ���Ĳ�ʽ���,����0����"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int foodnum;//��ʽ���
	foodnum=transform(str);//�ַ���ת��Ϊ����

	if(foodnum!=0)
	{
		while(foodnum!=0)
		{
			bool check=true;//���Ҫɾ���Ĳ�ʽ�Ƿ񱻶�����Ĭ��Ϊû������
			if(foodnum>menulist.size()||foodnum<0)
			{
				system("cls");
				cout<<endl;
				cout<<"�Բ�������������������롣"<<endl; 
				cout<<endl;
			}
			else
			{
				for(int i=0;i<orderlist.size();i++)//����Ƿ񱻶���
				{
					if(orderlist[i].getFoodName()==menulist[foodnum-1].getFoodName())
					{
						system("cls");
						cout<<endl;
						cout<<"�˲�ʽ�п��˶���������ϵ�ͻ�ȡ����������ɾ����"<<endl;
						cout<<endl;
						check=false;//�˵��ѱ��������޷�ɾ��
						break;
					}
				}
				if(check)//��û������
				{
					cout<<"ȷ��ɾ��������Y����������ֵ���ء�"<<endl;
					char ch;
					cin>>ch;
					if(ch=='Y'||ch=='y')
					{
						string foodname=menulist[foodnum-1].getFoodName();//��������ͼ۸����ں���չʾ��ɾ������
						double price=menulist[foodnum-1].getPrice();
						menulist.erase(menulist.begin()+foodnum-1);//ɾ���˵�
						system("cls");
						cout<<endl;
						cout<<left<<"# "<<setw(25)<<foodname<<" ��"<<setw(7)<<fixed<<setprecision(2)<<price
							<<" ɾ���ɹ���"<<endl;//ɾ���ɹ���ʾ��
					}
					else 
						system("cls");
				}
			}
			displaymenu();//��ӡ�˵�
			cout<<endl;
			cout<<"������Ҫɾ���Ĳ�ʽ��ţ�����0���أ�"<<endl;
			cin>>str;//��ֹ������������֣���string���

			//�ж������Ƿ�Ϸ�
			bool bcheck=checkin(str);//���з����ַ���false
			while(!bcheck)//bcheck=false����������
			{
				cout<<endl;
				cout<<"�����������������Ҫɾ���Ĳ�ʽ���,����0����"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			foodnum=transform(str);//�ַ���ת��Ϊ����
		}
		system("cls");
		cout<<endl;
		cout<<"ɾ������������"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"ɾ������������"<<endl;
	}
}

void changemenu()//�޸Ĳ˵�
{
	while(1)
	{
		displaymenu();//��ӡ�˵�
		cout<<endl;
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"��ѡ����������� A.��Ӳ˵�   B.ɾ���˵�   C.����   D.ֱ���˳�"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a') 
		{
			system("cls");
			adddish();//��Ӳ˵�
		}
		else
		if(ch=='B'||ch=='b')
		{
			system("cls");
			deletedish();//ɾ���˵�
		}
		else
		if(ch=='C'||ch=='c')
		{
			system("cls");
			return;//����
		}
		if(ch=='D'||ch=='d')
		{
			 cout<<"����δ���棬�Ƿ�Ҫ�˳���������Y�����˳��������򷵻أ�"<<endl;//ѯ���Ƿ񲻱����˳�
			 char c;
			 cin>>c;
			 if(c=='Y'||c=='y')
				 exit(0);
			 else
				 system("cls");
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//�Ŵ���������
		{
			system("cls");
			cout<<endl;
			cout<<"�Բ�������������������롣"<<endl;
			cout<<endl;
		}
	}
}

void displayorder()//չʾ����
{
	cout<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	for(int i=0;i<orderlist.size();i++)
	{
		cout<<left<<"# "<<setw(3)<<i+1<<": "<<setw(10)<<orderlist[i].getPersonName()<<setw(25)
			<<orderlist[i].getFoodName()<<" ��"<<setw(7)<<fixed<<setprecision(2)<<orderlist[i].getPrice()
			<<" X"<<setw(3)<<orderlist[i].getNumber()<<" ����"<<setw(7)<<fixed<<setprecision(2)
			<<orderlist[i].getPrice()*orderlist[i].getNumber()
			<<"Ԫ";//����ʽչʾ
		if(orderlist[i].wasChecked()==true)//�ж��Ƿ�ȷ��
			cout<<" ��ȷ��"<<endl;
		else
			cout<<" δȷ��"<<endl;
	}
}

void checkorder()//ȷ�϶���
{
	if(orderlist.empty())//��ֹľ�ж���
	{
		cout<<endl;
		cout<<"�Բ������޶�����Ϣ"<<endl;
		cout<<endl;
		return;
	}

	system("cls");
	displayorder();//չʾ����
	cout<<endl;
	cout<<"������Ҫȷ�ϵĶ�����ţ�����0���أ�"<<endl;
	string str;//��ֹ������������֣���string���
	cin>>str;

	//�ж������Ƿ�Ϸ�
	bool bcheck=checkin(str);//���з����ַ���false
	while(!bcheck)//bcheck=false����������
	{
		cout<<endl;
		cout<<"�����������������Ҫȷ�ϵı��,����0����"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int ordernum;//�������
	ordernum=transform(str);//�ַ���ת��Ϊ����

	vector<Order*> order;//����modifyOrder��Ե�ʣ�������һ��װ��Order��ָ�������
	if(ordernum!=0)
	{
		while(ordernum!=0)
		{
			if(ordernum>orderlist.size()||ordernum<0)
			{
				system("cls");
				cout<<endl;
				cout<<"�Բ�������������������롣"<<endl;
				displayorder();//չʾ����������ȷ��ǰ��..��
			}
			else
				order.push_back(&orderlist[ordernum-1]);//��¼Ҫȷ�ϵĶ����ĵ�ַ

			cout<<endl;
			cout<<"������Ҫȷ�ϵ���һ�Ŷ�����ţ�����0���ȷ�����϶���������"<<endl;//�ɼ����޸Ķ��Ŷ���
			cin>>str;//��ֹ������������֣���string���

			//�ж������Ƿ�Ϸ�
			bool bcheck=checkin(str);//���з����ַ���false
			while(!bcheck)//bcheck=false����������
			{
				cout<<endl;
				cout<<"�����������������Ҫȷ�ϵ���һ�Ŷ������,����0����"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			ordernum=transform(str);//�ַ���ת��Ϊ����
		}
		//��ʽȷ�϶�������
		Seller* seller;//���ڴ��ݵ�Seller�е�modifyOrder(vector<Order*>��Ե�ʣ�����һ��Seller���͵�ָ��
		seller=new Seller();
		seller->modifyOrder(order); //ȷ�϶���
		delete seller;

		system("cls");
		cout<<endl;
		cout<<"�˵��ɹ�ȷ�ϣ�"<<endl; 
		cout<<"�˵�ȷ�ϲ����������Զ����ء�"<<endl;
		cout<<endl;
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"����ȷ�ϲ˵�������"<<endl;
		cout<<endl;
	}
}

void functionseller()//����ϵͳ
{
	system("cls");
	while(1)
	{
		cout<<endl;
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"��ѡ����������� A.���/ɾ���˵� B.��ѯ/ȷ�϶��� C.���沢�˳� D.ֱ���˳�"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			system("cls");
			changemenu();//�޸Ĳ˵�
		}
		else
		if(ch=='B'||ch=='b') 
		{
			system("cls");
			checkorder();//ȷ�϶���
		}
		else
		if(ch=='C'||ch=='c')
		{
			cout<<endl;
			cout<<"******************"<<endl;
			cout<<"ף��������һ�죡"<<endl;
			cout<<"******************"<<endl;
			for(int i=0;i<100000000;i++){}//������������Ǿ仰��΢ͣ��һ��
			save();//����˵��붩��
			exit(0);
		}
		else
		if(ch=='D'||ch=='d')
		{
			cout<<endl;
			cout<<"����δ���棬�Ƿ�Ҫ�˳���������Y�����˳������������򷵻أ�"<<endl;//ѯ���Ƿ񲻱����˳�
			char c;
			cin>>c;
			if(c=='Y'||c=='y')
				exit(0);
			system("cls");
			continue;
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//�Ŵ���������
		{
			system("cls");
			cout<<endl;
			cout<<"�Բ�������������������롣"<<endl;
			cout<<endl;
		}
	}  
}

void makeorder()//�¶���
{
	if(menulist.empty())//�ж���ľ�в˵�
	{
		cout<<endl;
		cout<<"���޲˵������Ժ�"<<endl;
		cout<<endl;
		return; 
	}

	displaymenu();//չʾ�˵�
	cout<<endl;
	cout<<"�����������һ�ֲ�ʽ����ţ�����0���أ�"<<endl;
	string str;//��ֹ������������֣���string���
	cin>>str;

	//�ж������Ƿ�Ϸ�
	bool bcheck=checkin(str);//���з����ַ���false
	while(!bcheck)//bcheck=false����������
	{
		cout<<endl;
		cout<<"���������������������Ĳ�ʽ���,����0����"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int foodnum;//��ʽ���
	foodnum=transform(str);//�ַ���ת��Ϊ����

	if(foodnum!=0)
	{
		while(foodnum!=0)
		{
			if(foodnum>menulist.size()||foodnum<0)//�Ŵ���ֹ��Ų������з�Χ��
			{
				system("cls");
				cout<<endl;
				cout<<"�Բ�������������������롣"<<endl; 
			}
			else
			{
				cout<<"��������Ҫ������������"<<endl; 
				string str1;//��ֹ������������֣���string���
				cin>>str1;

				//�ж������Ƿ�Ϸ�
				bool bcheck=checkin(str1);//���з����ַ���false
				while(!bcheck)//bcheck=false����������
				{
					cout<<endl;
					cout<<"���������������������Ĳ�ʽ���,����0����"<<endl;
					cin>>str1;
					bcheck=checkin(str1);
				}

				int num;//��������
				num=transform(str1);//�ַ���ת��Ϊ����
				
				orderlist.push_back(Order(buyer->getPersonName(),buyer->getPhoneNumber(),
					buyer->getAddress(),menulist[foodnum-1].getFoodName(),menulist[foodnum-1].
					getPrice(),num,false));//���������Ϣ�Ͷ�����Ϣ
				system("cls");
				cout<<endl;
				cout<<"���Ѷ��� "<<menulist[foodnum-1].getFoodName()<<" X"<<num
					<<" ����"<<setw(7)<<fixed<<setprecision(2)<<menulist[foodnum-1].getPrice()*num
					<<"Ԫ"<<endl;//����ʽչʾһ�������Ϣ�Ͷ�����Ϣ�������ִ���ɼ�ʱɾ��
				cout<<endl;
				cout<<"�ɹ��ύ������Ϣ����л�ݹˣ�"<<endl;
			}
			cout<<endl;
			displaymenu();//չʾ�˵�
			cout<<endl;
			cout<<"�����������һ��ʳƷ����ţ�����0���أ�"<<endl;
			cin>>str;//��ֹ������������֣���string���

			//�ж������Ƿ�Ϸ�
			bool bcheck=checkin(str);//���з����ַ���false
			while(!bcheck)//bcheck=false����������
			{
				cout<<endl;
				cout<<"�����������������һ������Ĳ�ʽ���,����0����"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			foodnum=transform(str);//�ַ���ת��Ϊ����

		}
		system("cls");
		cout<<endl;
		cout<<"��л�ݹˣ���ӭ�ٴι��٣�"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"��ӭ�ٴι��٣�"<<endl;
	}
}

void cancleorder()
{
	if(orderlist.empty())//��ֹľ�ж���
	{
		cout<<endl;
		cout<<"�Բ������޶�����Ϣ"<<endl;
		cout<<endl;
		return;
	}

	cout<<endl;
	bool check=false;//Ĭ�ϸÿͻ�û�ж���
	for(int i=0;i<orderlist.size();i++)
		if(orderlist[i].getPersonName()==buyer->getPersonName()
			&&orderlist[i].getPhoneNumber()==buyer->getPhoneNumber())//�Ա��µ������֡��绰��ȷ���Ƿ�Ϊ�ÿͻ��Ķ���
		{
			cout<<left<<"# "<<setw(3)<<i+1<<setw(25)<<orderlist[i].getFoodName()
				<<" ��"<<setw(7)<<fixed<<setprecision(2)<<orderlist[i].getPrice()
				<<" X"<<orderlist[i].getNumber()<<"  ";//����ʽ������ڸÿͻ��Ķ���
			if(orderlist[i].wasChecked())//����Ƿ�ȷ��
				cout<<" ������ȷ��"<<endl;
			else
				cout<<" ����δȷ��"<<endl;
			check=true;//�ÿͻ��ж���
		}
	if(check)
	{
		cout<<endl;
		cout<<"������Ҫȡ����һ�Ŷ����ı��,����0����"<<endl;
		string str;//��ֹ������������֣���string���
		cin>>str;

		//�ж������Ƿ�Ϸ�
		bool bcheck=checkin(str);
		while(!bcheck)//bcheck=false����������
		{
			cout<<endl;
			cout<<"�����������������Ҫȡ����һ�Ŷ����ı��,����0����"<<endl;
			cin>>str;
			bcheck=checkin(str);
		}

		int num;//�������
		num=transform(str);//�ַ���ת��Ϊ����

		vector<Order*> order;
		while(num!=0)
		{
			if(num>orderlist.size()||num<0)//�Ŵ���ֹ��Ų������з�Χ��
			{
				cout<<endl;
				cout<<"�Բ�������������������롣"<<endl;
			}
			else
			{
				if(orderlist[num-1].getPersonName()==buyer->getPersonName()
					&&orderlist[num-1].getPhoneNumber()==buyer->getPhoneNumber())//���ö����ǲ������ڸÿͻ�����ֹ��ɾ
					order.push_back(&orderlist[num-1]);//����Ҫɾ�Ķ����ĵ�ַ
				else
					cout<<"�Բ��𣬸ñ�ŵĶ��������ô������͵绰���������������롣"<<endl;
					cout<<endl;
			}
			cout<<"������Ҫȡ������һ�Ŷ����ı��,����0���ȡ��������ѡ����������"<<endl;
			cin>>str;//��ֹ������������֣���string���

			//�ж������Ƿ�Ϸ�
			bool bcheck=checkin(str);//���з����ַ���false
			while(!bcheck)//bcheck=false����������
			{
				cout<<endl;
				cout<<"�����������������Ҫȡ������һ�Ŷ����ı��,����0����"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			num=transform(str);//�ַ���ת��Ϊ����
		}

		buyer->modifyOrder(order);//���ݵ�Buyer�е�modifyOrder(vector<Order*>��order��ָ���Ҫɾ���Ķ�����cancled���true
		for(int i=0;i<orderlist.size();i++)
			if(orderlist[i].wasCanceled())//ɾ��canceled=true�Ķ���
			{
				orderlist.erase(orderlist.begin()+i);
				i--;//�Ƴ�֮��orderlist.size()���һ������i--���ܱ�֤����©ɾ
			}

		cout<<endl;
		cout<<"ȡ������������������ӭ�´ι��٣�"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"�Բ�����δ���ͻ����Ǳ��涩����"<<endl;
	}
}

void functionbuyer()
{
	system("cls");
	cout<<endl;
	cout<<"��������������������ַ��ѡ�񲻱���ֱ���˳�"<<endl;
	cout<<"�Ͽͻ��������ϴν���ʱ���������绰�������޷��鿴��������"<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	string personname,phonenumber,address;
	cout<<"�𾴵Ŀͻ�����������������(���ִ�Сд)��"<<endl;
	cin>>personname;
	cout<<endl;
	cout<<"�𾴵Ŀͻ������������ĵ绰��8λ/11λ����"<<endl;
	cin>>phonenumber;
	while(phonenumber.size()!=8&&phonenumber.size()!=11||!checkin(phonenumber))//��ֹ�绰����λ������
	{
		cout<<endl;
		cout<<"�Բ���������ĵ绰��ʽ��λ����8λ/11λ���������������룺"<<endl;
		cout<<endl;
		cout<<"�𾴵Ŀͻ������������ĵ绰��8λ/11λ����"<<endl;
		cin>>phonenumber;
	}
	cout<<endl;
	cout<<"�𾴵Ŀͻ������������ĵ�ַ��"<<endl;
	cin>>address;
	cout<<endl;
	cout<<"����Ϣ������ֱ���˳�ϵͳ���µ��롣"<<endl;
	buyer=new Buyer(personname,phonenumber,address);//��̬����ͻ���Ϣ���¶���ʱ�ٱ��浽orderlist��

	while(1)
	{
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"��ѡ�����������A.���� B.��ѯ����/�˶� C.���沢�˳� D.ֱ���˳�"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			system("cls");
			makeorder();//�¶���
		}
		else
			if(ch=='B'||ch=='b') 
		{
			system("cls");
			cancleorder();//��ѯ/�˶�
		}
		else
		if(ch=='C'||ch=='c')
		{
			cout<<endl;
			cout<<"***********************"<<endl;
			cout<<"��л�ݹˣ���ӭ�ٴι��٣�"<<endl;
			cout<<"***********************"<<endl;
			for(int i=0;i<100000000;i++){}//����ʹ���Ͻ�����ͣ����΢��һ��ʱ��
			save();
			exit(0);
		}
		else
		if(ch=='D'||ch=='d')
		{
			cout<<endl;
			cout<<"����δ���棬�Ƿ�Ҫ�˳���������Y�����˳������������򷵻أ�"<<endl;
			char c;
			cin>>c;
			if(c=='Y'||c=='y')
				exit(0);
			continue;
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//�Ŵ���������
		{
			system("cls");
			cout<<endl;
			cout<<"�Բ�������������������롣 "<<endl;
			cout<<endl;
		}
		}
}

int main()//�ҽ�������
{
	cout<<endl;
	cout<<"��ӭ������ձȺ��ʳǶ���ϵͳ"<<endl;
	char ch='D';
	while(ch!='A'&&ch!='B'&&ch!='C'&&ch!='a'&&ch!='b'&&ch!='c')
	{
		cout<<"================================================================================"<<endl;//�ҽзָ���
		cout<<endl;
		cout<<"�������ǣ� A.�̼�  B.�ͻ�  C.�򿪴��ˣ��˳�ϵͳ"<<endl;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			loadmenulist();//����˵�
			loadorderlist();//���붩��
			functionseller();//�������Ҳ���
		}
		else
		if(ch=='B'||ch=='b') 
		{
			loadmenulist();//����˵�
			loadorderlist();//���붩��
			functionbuyer();//������Ҳ���
		}
		else
		if(ch=='C'||ch=='c')
		{
			exit(0);//ֱ���˳�
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c')//�Ŵ����³�ȥ
		{
			system("cls");
			cout<<endl;
			cout<<"�Բ�������������������롣"<<endl;
			cout<<endl;
		}
	}
}