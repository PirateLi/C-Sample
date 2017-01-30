#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include"User.h"
using namespace std;

vector<Menu> menulist;//用于载入和保存菜单信息
vector<Order> orderlist;//用于载入和保存订单信息
Buyer *buyer;//1.用于临时储存用户信息下订单时保存到orderlist中 2.用于传递到Buyer中的modifyOrder(vector<Order*>

void loadmenulist()//载入菜单
{
	int menunum;//文件开头的菜单数
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

void loadorderlist()//载入订单
{
	int ordernum;//文件开头的订单数
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

void save()//保存菜单与订单
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

bool checkin(string str)//检测客户输入是否有非数字
{
	for(int i=0;i<str.size();i++)
		if(str[i]<'0'||str[i]>'9')
			return false;
	return true;
}

int transform(string str)//字符串转化为数字
{
	int n=0;
	for(int i=0;i<str.size();i++)
	{
		n=n*10;
		n+=str[i]-'0';
	}
	return n;
}

void displaymenu()//展示菜单
{
	cout<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	if(menulist.empty())//若没有菜单
		cout<<"对不起，您尚未添加菜单信息。"<<endl;
	else
		for(int i=0;i<menulist.size();i++)//打印菜单
			cout<<left<<"# "<<setw(3)<<i+1<<": "<<setw(25)<<menulist[i].getFoodName()
				<<" ￥"<<setw(7)<<fixed<<setprecision(2)<<menulist[i].getPrice()<<endl;
}

void adddish()//增加菜式
{
	system("cls");
	displaymenu();//打印菜单
	cout<<endl;
	string name;
	double price;
	cout<<"请输入新菜式名称（12个字以内）,输入0返回："<<endl;
	cin>>name;
	if(name[0]!='0')
	{
		cout<<"请输入新菜式价格："<<endl;
		cin>>price;
		menulist.push_back(Menu(name,price));//储存新菜式
		system("cls");
		cout<<endl;
		cout<<"添加新菜式"<<left<<setw(25)<<name
				  <<" ￥"<<setw(7)<<fixed<<setprecision(2)<<price<<"成功！"<<endl;
		cout<<"添加菜式操作结束。";
		cout<<endl;
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"添加菜式操作结束。";
		cout<<endl;
	}
}

void deletedish()//删除菜式
{
	displaymenu();//打印菜单
	cout<<endl;
	cout<<"请输入要删除的菜式编号，输入0返回"<<endl; 
	string str;//防止错误输入非数字，用string检测
	cin>>str;

	//判断输入是否合法
	bool bcheck=checkin(str);//若有非数字返回false
	while(!bcheck)//bcheck=false则重新输入
	{
		cout<<endl;
		cout<<"输入错误，请重新输入要删除的菜式编号,输入0返回"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int foodnum;//菜式编号
	foodnum=transform(str);//字符串转化为数字

	if(foodnum!=0)
	{
		while(foodnum!=0)
		{
			bool check=true;//检测要删除的菜式是否被订购，默认为没被订购
			if(foodnum>menulist.size()||foodnum<0)
			{
				system("cls");
				cout<<endl;
				cout<<"对不起，输入错误，请重新输入。"<<endl; 
				cout<<endl;
			}
			else
			{
				for(int i=0;i<orderlist.size();i++)//检查是否被订购
				{
					if(orderlist[i].getFoodName()==menulist[foodnum-1].getFoodName())
					{
						system("cls");
						cout<<endl;
						cout<<"此菜式有客人订购，请联系客户取消订单后再删除。"<<endl;
						cout<<endl;
						check=false;//菜单已被订购，无法删除
						break;
					}
				}
				if(check)//若没被订购
				{
					cout<<"确定删除请输入Y，输入其他值返回。"<<endl;
					char ch;
					cin>>ch;
					if(ch=='Y'||ch=='y')
					{
						string foodname=menulist[foodnum-1].getFoodName();//保存菜名和价格用于后面展示所删除内容
						double price=menulist[foodnum-1].getPrice();
						menulist.erase(menulist.begin()+foodnum-1);//删除菜单
						system("cls");
						cout<<endl;
						cout<<left<<"# "<<setw(25)<<foodname<<" ￥"<<setw(7)<<fixed<<setprecision(2)<<price
							<<" 删除成功！"<<endl;//删除成功提示语
					}
					else 
						system("cls");
				}
			}
			displaymenu();//打印菜单
			cout<<endl;
			cout<<"请输入要删除的菜式编号，输入0返回："<<endl;
			cin>>str;//防止错误输入非数字，用string检测

			//判断输入是否合法
			bool bcheck=checkin(str);//若有非数字返回false
			while(!bcheck)//bcheck=false则重新输入
			{
				cout<<endl;
				cout<<"输入错误，请重新输入要删除的菜式编号,输入0返回"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			foodnum=transform(str);//字符串转化为数字
		}
		system("cls");
		cout<<endl;
		cout<<"删除操作结束！"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"删除操作结束！"<<endl;
	}
}

void changemenu()//修改菜单
{
	while(1)
	{
		displaymenu();//打印菜单
		cout<<endl;
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"请选择所需操作： A.添加菜单   B.删除菜单   C.返回   D.直接退出"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a') 
		{
			system("cls");
			adddish();//添加菜单
		}
		else
		if(ch=='B'||ch=='b')
		{
			system("cls");
			deletedish();//删除菜单
		}
		else
		if(ch=='C'||ch=='c')
		{
			system("cls");
			return;//返回
		}
		if(ch=='D'||ch=='d')
		{
			 cout<<"您还未保存，是否要退出？（输入Y继续退出，其他则返回）"<<endl;//询问是否不保存退出
			 char c;
			 cin>>c;
			 if(c=='Y'||c=='y')
				 exit(0);
			 else
				 system("cls");
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//排错，重新输入
		{
			system("cls");
			cout<<endl;
			cout<<"对不起，输入错误，请重新输入。"<<endl;
			cout<<endl;
		}
	}
}

void displayorder()//展示订单
{
	cout<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	for(int i=0;i<orderlist.size();i++)
	{
		cout<<left<<"# "<<setw(3)<<i+1<<": "<<setw(10)<<orderlist[i].getPersonName()<<setw(25)
			<<orderlist[i].getFoodName()<<" ￥"<<setw(7)<<fixed<<setprecision(2)<<orderlist[i].getPrice()
			<<" X"<<setw(3)<<orderlist[i].getNumber()<<" 共："<<setw(7)<<fixed<<setprecision(2)
			<<orderlist[i].getPrice()*orderlist[i].getNumber()
			<<"元";//按格式展示
		if(orderlist[i].wasChecked()==true)//判断是否被确认
			cout<<" 已确认"<<endl;
		else
			cout<<" 未确认"<<endl;
	}
}

void checkorder()//确认订单
{
	if(orderlist.empty())//防止木有订单
	{
		cout<<endl;
		cout<<"对不起，暂无订单信息"<<endl;
		cout<<endl;
		return;
	}

	system("cls");
	displayorder();//展示订单
	cout<<endl;
	cout<<"请输入要确认的订单编号，输入0返回："<<endl;
	string str;//防止错误输入非数字，用string检测
	cin>>str;

	//判断输入是否合法
	bool bcheck=checkin(str);//若有非数字返回false
	while(!bcheck)//bcheck=false则重新输入
	{
		cout<<endl;
		cout<<"输入错误，请重新输入要确认的编号,输入0返回"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int ordernum;//订单编号
	ordernum=transform(str);//字符串转化为数字

	vector<Order*> order;//由于modifyOrder的缘故，先申明一个装着Order类指针的容器
	if(ordernum!=0)
	{
		while(ordernum!=0)
		{
			if(ordernum>orderlist.size()||ordernum<0)
			{
				system("cls");
				cout<<endl;
				cout<<"对不起，输入错误，请重新输入。"<<endl;
				displayorder();//展示订单（还是确认前的..）
			}
			else
				order.push_back(&orderlist[ordernum-1]);//记录要确认的订单的地址

			cout<<endl;
			cout<<"请输入要确认的另一张订单编号，输入0完成确认以上订单操作："<<endl;//可继续修改多张订单
			cin>>str;//防止错误输入非数字，用string检测

			//判断输入是否合法
			bool bcheck=checkin(str);//若有非数字返回false
			while(!bcheck)//bcheck=false则重新输入
			{
				cout<<endl;
				cout<<"输入错误，请重新输入要确认的另一张订单编号,输入0返回"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			ordernum=transform(str);//字符串转化为数字
		}
		//正式确认订单操作
		Seller* seller;//用于传递到Seller中的modifyOrder(vector<Order*>的缘故，设置一个Seller类型的指针
		seller=new Seller();
		seller->modifyOrder(order); //确认订单
		delete seller;

		system("cls");
		cout<<endl;
		cout<<"菜单成功确认！"<<endl; 
		cout<<"菜单确认操作结束，自动返回。"<<endl;
		cout<<endl;
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"结束确认菜单操作！"<<endl;
		cout<<endl;
	}
}

void functionseller()//卖家系统
{
	system("cls");
	while(1)
	{
		cout<<endl;
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"请选择所需操作： A.添加/删除菜单 B.查询/确认订单 C.保存并退出 D.直接退出"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			system("cls");
			changemenu();//修改菜单
		}
		else
		if(ch=='B'||ch=='b') 
		{
			system("cls");
			checkorder();//确认订单
		}
		else
		if(ch=='C'||ch=='c')
		{
			cout<<endl;
			cout<<"******************"<<endl;
			cout<<"祝您有愉快的一天！"<<endl;
			cout<<"******************"<<endl;
			for(int i=0;i<100000000;i++){}//这个是让以上那句话稍微停留一下
			save();//保存菜单与订单
			exit(0);
		}
		else
		if(ch=='D'||ch=='d')
		{
			cout<<endl;
			cout<<"您还未保存，是否要退出？（输入Y继续退出，输入其他则返回）"<<endl;//询问是否不保存退出
			char c;
			cin>>c;
			if(c=='Y'||c=='y')
				exit(0);
			system("cls");
			continue;
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//排错，重新输入
		{
			system("cls");
			cout<<endl;
			cout<<"对不起，输入错误，请重新输入。"<<endl;
			cout<<endl;
		}
	}  
}

void makeorder()//下订单
{
	if(menulist.empty())//判断有木有菜单
	{
		cout<<endl;
		cout<<"暂无菜单，请稍后"<<endl;
		cout<<endl;
		return; 
	}

	displaymenu();//展示菜单
	cout<<endl;
	cout<<"请输入所需的一种菜式的序号，输入0返回："<<endl;
	string str;//防止错误输入非数字，用string检测
	cin>>str;

	//判断输入是否合法
	bool bcheck=checkin(str);//若有非数字返回false
	while(!bcheck)//bcheck=false则重新输入
	{
		cout<<endl;
		cout<<"输入错误，请重新输入所需的菜式编号,输入0返回"<<endl;
		cin>>str;
		bcheck=checkin(str);
	}

	int foodnum;//菜式编号
	foodnum=transform(str);//字符串转化为数字

	if(foodnum!=0)
	{
		while(foodnum!=0)
		{
			if(foodnum>menulist.size()||foodnum<0)//排错，防止序号不在已有范围内
			{
				system("cls");
				cout<<endl;
				cout<<"对不起，输入错误，请重新输入。"<<endl; 
			}
			else
			{
				cout<<"请输入想要订购的数量："<<endl; 
				string str1;//防止错误输入非数字，用string检测
				cin>>str1;

				//判断输入是否合法
				bool bcheck=checkin(str1);//若有非数字返回false
				while(!bcheck)//bcheck=false则重新输入
				{
					cout<<endl;
					cout<<"输入错误，请重新输入所需的菜式编号,输入0返回"<<endl;
					cin>>str1;
					bcheck=checkin(str1);
				}

				int num;//订购数量
				num=transform(str1);//字符串转化为数字
				
				orderlist.push_back(Order(buyer->getPersonName(),buyer->getPhoneNumber(),
					buyer->getAddress(),menulist[foodnum-1].getFoodName(),menulist[foodnum-1].
					getPrice(),num,false));//储存买家信息和订单信息
				system("cls");
				cout<<endl;
				cout<<"您已订购 "<<menulist[foodnum-1].getFoodName()<<" X"<<num
					<<" 共："<<setw(7)<<fixed<<setprecision(2)<<menulist[foodnum-1].getPrice()*num
					<<"元"<<endl;//按格式展示一次买家信息和订单信息，若发现错买可及时删除
				cout<<endl;
				cout<<"成功提交订餐信息，多谢惠顾！"<<endl;
			}
			cout<<endl;
			displaymenu();//展示菜单
			cout<<endl;
			cout<<"请输入所需的一种食品的序号，输入0返回："<<endl;
			cin>>str;//防止错误输入非数字，用string检测

			//判断输入是否合法
			bool bcheck=checkin(str);//若有非数字返回false
			while(!bcheck)//bcheck=false则重新输入
			{
				cout<<endl;
				cout<<"输入错误，请重新输入一种所需的菜式编号,输入0返回"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			foodnum=transform(str);//字符串转化为数字

		}
		system("cls");
		cout<<endl;
		cout<<"多谢惠顾，欢迎再次光临！"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"欢迎再次光临！"<<endl;
	}
}

void cancleorder()
{
	if(orderlist.empty())//防止木有订单
	{
		cout<<endl;
		cout<<"对不起，暂无订单信息"<<endl;
		cout<<endl;
		return;
	}

	cout<<endl;
	bool check=false;//默认该客户没有订单
	for(int i=0;i<orderlist.size();i++)
		if(orderlist[i].getPersonName()==buyer->getPersonName()
			&&orderlist[i].getPhoneNumber()==buyer->getPhoneNumber())//对比下单的名字、电话来确认是否为该客户的订单
		{
			cout<<left<<"# "<<setw(3)<<i+1<<setw(25)<<orderlist[i].getFoodName()
				<<" ￥"<<setw(7)<<fixed<<setprecision(2)<<orderlist[i].getPrice()
				<<" X"<<orderlist[i].getNumber()<<"  ";//按格式输出属于该客户的订单
			if(orderlist[i].wasChecked())//输出是否被确认
				cout<<" 订单已确认"<<endl;
			else
				cout<<" 订单未确认"<<endl;
			check=true;//该客户有订单
		}
	if(check)
	{
		cout<<endl;
		cout<<"请输入要取消的一张订单的编号,输入0返回"<<endl;
		string str;//防止错误输入非数字，用string检测
		cin>>str;

		//判断输入是否合法
		bool bcheck=checkin(str);
		while(!bcheck)//bcheck=false则重新输入
		{
			cout<<endl;
			cout<<"输入错误，请重新输入要取消的一张订单的编号,输入0返回"<<endl;
			cin>>str;
			bcheck=checkin(str);
		}

		int num;//订单编号
		num=transform(str);//字符串转化为数字

		vector<Order*> order;
		while(num!=0)
		{
			if(num>orderlist.size()||num<0)//排错，防止序号不在已有范围内
			{
				cout<<endl;
				cout<<"对不起，输入错误，请重新输入。"<<endl;
			}
			else
			{
				if(orderlist[num-1].getPersonName()==buyer->getPersonName()
					&&orderlist[num-1].getPhoneNumber()==buyer->getPhoneNumber())//检查该订单是不是属于该客户，防止误删
					order.push_back(&orderlist[num-1]);//储存要删的订单的地址
				else
					cout<<"对不起，该编号的订单不是用此姓名和电话订购，请重新输入。"<<endl;
					cout<<endl;
			}
			cout<<"请输入要取消的另一张订单的编号,输入0完成取消以上所选订单操作。"<<endl;
			cin>>str;//防止错误输入非数字，用string检测

			//判断输入是否合法
			bool bcheck=checkin(str);//若有非数字返回false
			while(!bcheck)//bcheck=false则重新输入
			{
				cout<<endl;
				cout<<"输入错误，请重新输入要取消的另一张订单的编号,输入0返回"<<endl;
				cin>>str;
				bcheck=checkin(str);
			}

			num=transform(str);//字符串转化为数字
		}

		buyer->modifyOrder(order);//传递到Buyer中的modifyOrder(vector<Order*>把order中指向的要删除的订单的cancled变成true
		for(int i=0;i<orderlist.size();i++)
			if(orderlist[i].wasCanceled())//删除canceled=true的订单
			{
				orderlist.erase(orderlist.begin()+i);
				i--;//移除之后orderlist.size()会减一，所以i--才能保证不会漏删
			}

		cout<<endl;
		cout<<"取消订单操作结束，欢迎下次光临！"<<endl; 
	}
	else
	{
		system("cls");
		cout<<endl;
		cout<<"对不起，您未订餐或忘记保存订单。"<<endl;
	}
}

void functionbuyer()
{
	system("cls");
	cout<<endl;
	cout<<"若有输入错误请在输入地址后选择不保存直接退出"<<endl;
	cout<<"老客户请输入上次进入时的姓名及电话，否则无法查看以往订单"<<endl;
	cout<<"================================================================================"<<endl;
	cout<<endl;
	string personname,phonenumber,address;
	cout<<"尊敬的客户，请输入您的姓名(区分大小写)："<<endl;
	cin>>personname;
	cout<<endl;
	cout<<"尊敬的客户，请输入您的电话（8位/11位）："<<endl;
	cin>>phonenumber;
	while(phonenumber.size()!=8&&phonenumber.size()!=11||!checkin(phonenumber))//防止电话号码位数错误
	{
		cout<<endl;
		cout<<"对不起，您输入的电话格式或位数（8位/11位）错误，请重新输入："<<endl;
		cout<<endl;
		cout<<"尊敬的客户，请输入您的电话（8位/11位）："<<endl;
		cin>>phonenumber;
	}
	cout<<endl;
	cout<<"尊敬的客户，请输入您的地址："<<endl;
	cin>>address;
	cout<<endl;
	cout<<"若信息有误请直接退出系统重新登入。"<<endl;
	buyer=new Buyer(personname,phonenumber,address);//动态储存客户信息，下订单时再保存到orderlist中

	while(1)
	{
		cout<<"================================================================================"<<endl;
		cout<<endl;
		cout<<"请选择所需操作：A.订餐 B.查询订单/退订 C.保存并退出 D.直接退出"<<endl;
		char ch;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			system("cls");
			makeorder();//下订单
		}
		else
			if(ch=='B'||ch=='b') 
		{
			system("cls");
			cancleorder();//查询/退订
		}
		else
		if(ch=='C'||ch=='c')
		{
			cout<<endl;
			cout<<"***********************"<<endl;
			cout<<"多谢惠顾，欢迎再次光临！"<<endl;
			cout<<"***********************"<<endl;
			for(int i=0;i<100000000;i++){}//用于使以上结束语停留稍微长一点时间
			save();
			exit(0);
		}
		else
		if(ch=='D'||ch=='d')
		{
			cout<<endl;
			cout<<"您还未保存，是否要退出？（输入Y继续退出，输入其他则返回）"<<endl;
			char c;
			cin>>c;
			if(c=='Y'||c=='y')
				exit(0);
			continue;
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c'&&ch!='D'&&ch!='d')//排错，重新输入
		{
			system("cls");
			cout<<endl;
			cout<<"对不起，输入错误，请重新输入。 "<<endl;
			cout<<endl;
		}
		}
}

int main()//我叫主函数
{
	cout<<endl;
	cout<<"欢迎进入加勒比海鲜城订餐系统"<<endl;
	char ch='D';
	while(ch!='A'&&ch!='B'&&ch!='C'&&ch!='a'&&ch!='b'&&ch!='c')
	{
		cout<<"================================================================================"<<endl;//我叫分割线
		cout<<endl;
		cout<<"请问您是： A.商家  B.客户  C.打开错了，退出系统"<<endl;
		cin>>ch;
		if(ch=='A'||ch=='a')
		{
			loadmenulist();//载入菜单
			loadorderlist();//载入订单
			functionseller();//运行卖家部分
		}
		else
		if(ch=='B'||ch=='b') 
		{
			loadmenulist();//载入菜单
			loadorderlist();//载入订单
			functionbuyer();//运行买家部分
		}
		else
		if(ch=='C'||ch=='c')
		{
			exit(0);//直接退出
		}
		else
		if(ch!='A'&&ch!='a'&&ch!='B'&&ch!='b'&&ch!='C'&&ch!='c')//排错，重新出去
		{
			system("cls");
			cout<<endl;
			cout<<"对不起，输入错误，请重新输入。"<<endl;
			cout<<endl;
		}
	}
}