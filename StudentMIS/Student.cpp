#include "Student.h"
#include <cstring>
#include <string>
#include <iomanip>
#include <conio.h>
using namespace std;

ifstream input_file;
ofstream output_file;

First::First()
{
	strcpy(mMajorDepName,"First");
//	inputPassword();		//
}

Second::Second()
{
	strcpy(mSecondDepName,"Second");
//	inputPassword();		//
}

void StudentBase::input()
{
	input_file.clear();
	input_file.open("BaseFile.dat");
	while (!input_file.eof())
	{
		Student newStudent;
		long mNum;
		input_file>>mNum>>newStudent.mName>>newStudent.mSex>>newStudent.mAge>>newStudent.mAddr;
		student[mNum]=newStudent;
	}
	input_file.close();
	cout<<"�����ɹ���"<<endl;
	system("pause");
	/*cout<<"�����ɹ��������������...";
	//char x;
	getchar();		//�ô�
	getchar();*/
}

map<long,Student> StudentBase::getStudent()
{
	return student;
}

void StudentBase::print()
{
	cout<<"ѧ��       ����    �Ա�       ����       סַ"<<endl;
	for (it=student.begin();it!=student.end();++it)
	{
		cout<<left<<setw(10)<<it->first;
		cout<<left<<setw(10)<<it->second.mName;
		if (it->second.mSex==0)	cout<<left<<setw(10)<<"��";
		else cout<<left<<setw(10)<<"Ů";
		cout<<left<<setw(10)<<it->second.mAge;
		cout<<left<<setw(10)<<it->second.mAddr;
		//cout<<left<<setw(20)<<student[i].mMajor;
		cout<<endl;
	}
	cout<<endl;

}

Student StudentBase::getStudentByNum(long num)
{
	return student[num];
}

void StudentBase::setStudent()
{
	print();
	cout<<"�Ƿ��޸���Ϣ��y/n��:";
	char x;
	while (cin>>x && x!='y' && x!='n') cout<<"����������������룺";
	if (x=='y')
	{
		while (1)
		{
			long num;
			cout<<"��������Ҫ�޸���Ϣ��ѧ��ѧ��(����-1������һ��)��";	
			while (cin>>num && student.find(num)==student.end() && num!=-1) cout<<"����������������룺";
			if (num==-1) return;
			while (1)
			{
				cout<<"��Ҫ�޸ĵ���Ϣ���ͣ�"<<endl;
				cout<<"1. ����"<<endl;
				cout<<"2. �Ա�"<<endl;
				cout<<"3. ����"<<endl;
				cout<<"4. ��ַ"<<endl;
				cout<<"0. ����"<<endl;
				cout<<"��������:";
				int n;
				while (cin>>n && (n<0 || n>4)) cout<<"����������������룺";
				cout<<"��������Ϣ��";
				if (n==0) break;
				if (n==1)
				{
					char name[20];
					cin>>name;
					strcpy(student[num].mName,name);
				}
				if (n==2)
				{
					string sex;
					cin>>sex;
					if (sex=="��") student[num].mSex=0;
					if (sex=="Ů") student[num].mSex=1;
				}
				if (n==3)
				{
					int age;
					cin>>age;
					student[num].mAge=age;
				}
				if (n==4)
				{
					char addr[30];
					cin>>addr;
					strcpy(student[num].mAddr,addr);
				}

				system("cls");
				print();
				cout<<"�޸ĳɹ�����ѡ�����:"<<endl;
				cout<<"1. �����޸ı�ѧ��������Ϣ"<<endl;
				cout<<"2. �޸�����ѧ������Ϣ"<<endl;
				cout<<"3. ����"<<endl;
				cout<<"�����룺";
				while (cin>>n && (n<1 || n>3)) cout<<"����������������룺";
				if (n==1) continue;
				if (n==2) break;
				if (n==3) 
				{
					output();
					return;
				}
			}	
		}
	}
	if (x=='n') return;
}
	

void StudentBase::output()
{
	output_file.open("BaseFile.dat");
	for (it=student.begin();it!=student.end();++it)
	{
		output_file<<it->first<<" "<<it->second.mName<<" "<<it->second.mSex<<" "<<it->second.mAge<<" "<<it->second.mAddr;
		if (it!=--student.end()) output_file<<endl;
	}
	output_file.close();
}

void StudentBase::selectOperation()
{
	int n;
	while (1)
	{
		system("cls");
		cout<<"��ӭ��������Ա��¼ϵͳ����ѡ���ܣ�"<<endl;
		cout<<"1. ����ѧ��������Ϣ��"<<endl;
		cout<<"2. ��ѯ/�޸�ѧ��������Ϣ"<<endl;
		cout<<"0. ����"<<endl;
		cout<<"������: ";
		while(cin>>n &&( n<0 || n>2)) cout<<"����������������룺 ";
		system("cls");
		if (n==1) input();
		if (n==2) setStudent();
		if (n==0) break;
	}
}

void First::selectOperation()
{
	int n;
	while (1)
	{
		system("cls");
		cout<<"��ӭ�������Ա��¼ϵͳ����ѡ���ܣ�"<<endl;
		cout<<"1. ¼��ɼ�"<<endl;
		cout<<"2. ��ѯ/�޸�ѧ���ɼ�"<<endl;
		cout<<"3. ��ѯѧ����Ϣ"<<endl;
		cout<<"4. ͳ������ѧ��"<<endl;
		cout<<"5. ͳ�Ʋ���ѧ��"<<endl;
		cout<<"0. ����"<<endl;
		cout<<"������: ";
		while(cin>>n &&( n<0 || n>5)) cout<<"����������������룺 ";
		system("cls");
		if (n==1) input();
		if (n==2) setScore();
		if (n==3) print();
		if (n==4) good();
		if (n==5) fail();
		if (n==0) break;
	}
}

void First::input()
{
	mFirstScore.clear();
	input_file.clear();
	input_file.open("First.dat");
	while (!input_file.eof())
	{
		Score newScore;
		long num;
		input_file>>num;
		newScore.mScore.resize(N);		
		for (int i=0;i<N;++i)
			input_file>>newScore.mScore[i];
		mFirstScore[num]=newScore;
	}
	input_file.close();
	cout<<"�����ɹ���"<<endl;
	system("pause");
	/*
	cout<<"�����ɹ�����������˳�....";
	getchar();
	getchar();*/
}

void First::print()
{
	Student tStudent;
	cout<<"ѧ��     ����      �Ա�       ����       סַ"<<endl;
	for (it=mFirstScore.begin();it!=mFirstScore.end();++it)
	{
		tStudent=getStudentByNum(it->first);
		cout<<left<<setw(10)<<it->first;
		cout<<left<<setw(10)<<tStudent.mName;
		if (tStudent.mSex==0) cout<<left<<setw(10)<<"��";
		else cout<<left<<setw(10)<<"Ů";
		cout<<left<<setw(10)<<tStudent.mAge;
		cout<<left<<setw(10)<<tStudent.mAddr;
		cout<<endl;
	}
	cout<<endl;
	cout<<"��ѯ�ɹ���"<<endl;
	system("pause");
}

void First::printScore()
{
	cout<<"ѧ��     ";
	for (int i=0;i<N;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;
	for (it=mFirstScore.begin();it!=mFirstScore.end();++it)
	{
		cout<<left<<setw(10)<<it->first;
		for (int j=0;j<N;++j)
			cout<<left<<setw(6)<<it->second.mScore[j];
		cout<<endl;
	}
	cout<<endl;
}

void First::setScore()
{
	printScore();
	cout<<"�Ƿ��޸ĳɼ���y/n��:";
	char x;
	while (cin>>x && x!='y' && x!='n') cout<<"����������������룺";
	if (x=='y')
	{
		while (1)
		{
			long num;
			cout<<"��������Ҫ�޸���Ϣ��ѧ��ѧ��(����-1������һ��)��";
			while (cin>>num && mFirstScore.find(num)==mFirstScore.end() && num!=-1) cout<<"����������������룺";
			if (num==-1) return;
			while (1)
			{
				it=mFirstScore.find(num);
				cout<<"��������Ҫ�޸ĵĿ�Ŀ���(����-1����ѧ������)��";
				int n;
				while (cin>>n && (n<1 || n>N) && n!=-1) cout<<"����������������룺";
				if (n==-1) break;
				cout<<"�������޸ĺ�ĳɼ���";
				int score;
				cin>>score;
				it->second.mScore[n-1]=score;
				
				system("cls");
				printScore();
				cout<<"�޸ĳɹ�����ѡ�����:"<<endl;
				cout<<"1. �����޸ı�ѧ��������Ŀ�ɼ�"<<endl;
				cout<<"2. �޸�����ѧ���ĳɼ�"<<endl;
				cout<<"3. ����"<<endl;
				cout<<"�����룺";
				while (cin>>n && (n<1 || n>3)) cout<<"����������������룺";
				if (n==1) continue;
				if (n==2) break;
				if (n==3) 
				{
					output();
					return;
				}
			}	
		}
	}
	if (x=='n') return;
}

void First::output()
{
	output_file.open("First.dat");
	for (it=mFirstScore.begin();it!=mFirstScore.end();++it)
	{
		output_file<<it->first;
		for (int i=0;i<N;++i)
			output_file<<" "<<it->second.mScore[i];
		if (it!=--mFirstScore.end()) output_file<<endl;
	}
	output_file.close();
}

void Second::output()
{
	output_file.open("Second.dat");
	for (it=mSecondScore.begin();it!=mSecondScore.end();++it)
	{
		output_file<<it->first;
		for (int i=0;i<M;++i)
			output_file<<" "<<it->second.mScore[i];
		output_file<<endl;
	}
	if (it!=--mSecondScore.end()) output_file.close();
}

void First::good()		
{
	cout<<"�ɼ������ѧ����"<<endl;
	cout<<"ѧ��   ";
	for (int i=0;i<N;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;

	output_file.open("FirstGood.dat");
	int sum=0;
	for (it=mFirstScore.begin();it!=mFirstScore.end();++it)
	{
		int count=0,count2=0;
		for (int i=0;i<N;++i)
		{
			if (it->second.mScore[i]>=85) count++;
			if (it->second.mScore[i]>=70) count2++;
		}
		if (count>=3 && count2==N)
		{
			it->second.isGood=true;
			sum++;
			output_file<<left<<setw(8)<<it->first;
			cout<<left<<setw(8)<<it->first;
			for (int j=0;j<N;++j) 
			{
				output_file<<left<<setw(6)<<it->second.mScore[j];
				cout<<left<<setw(6)<<it->second.mScore[j];
			}
			output_file<<endl;
			cout<<endl;
		}
		else it->second.isGood=false;
	}
	output_file.close();
	if (sum==0) cout<<endl<<"�޳ɼ�����ѧ����"<<endl<<endl;
	cout<<endl;
	cout<<"ͳ����ɣ�"<<endl;
	system("pause");
	/*
	cout<<"ͳ����ɣ���������˳�....";
	getchar();
	getchar();*/
}

void First::fail()		
{
	cout<<"��Ҫ������ѧ����"<<endl;
	cout<<"ѧ��   ";
	for (int i=0;i<N;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;

	output_file.open("FirstFail.dat");
	int sum=0;
	for (it=mFirstScore.begin();it!=mFirstScore.end();++it)
	{
		int count=0;
		for (int i=0;i<N;++i)
			if (it->second.mScore[i]<60) count++;
		if (count)
		{
			it->second.isFail=true;
			sum++;
			output_file<<left<<setw(8)<<it->first;
			cout<<left<<setw(8)<<it->first;
			for (int j=0;j<N;++j) 
			{
				output_file<<left<<setw(6)<<it->second.mScore[j];
				cout<<left<<setw(6)<<it->second.mScore[j];
			}
			output_file<<endl;
			cout<<endl;
		}
		else it->second.isFail=false;
	}
	output_file.close();
	if (sum==0) cout<<endl<<"����Ҫ������ѧ����"<<endl<<endl;
	cout<<endl;
	cout<<"ͳ����ɣ�"<<endl;
	system("pause");
	/*
	cout<<"ͳ����ɣ���������˳�....";
	getchar();
	getchar();*/
}

void Second::selectOperation()
{
	int n;
	while (1)
	{
		system("cls");
		cout<<"��ӭ�������Ա��¼ϵͳ����ѡ���ܣ�"<<endl;
		cout<<"1. ¼��ɼ�"<<endl;
		cout<<"2. ��ѯ/�޸�ѧ���ɼ�"<<endl;
		cout<<"3. ��ѯѧ����Ϣ"<<endl;
		cout<<"4. ͳ������ѧ��"<<endl;
		cout<<"5. ͳ�Ʋ���ѧ��"<<endl;
		cout<<"0. ����"<<endl;
		cout<<"������: ";
		while(cin>>n &&( n<0 || n>5)) cout<<"����������������룺 ";
		system("cls");
		if (n==1) input();
		if (n==2) setScore();
		if (n==3) print();
		if (n==4) good();
		if (n==5) fail();
		if (n==0) break;
	}
}

void Second::input()
{
	mSecondScore.clear();
	input_file.clear();
	input_file.open("Second.dat");
	while (!input_file.eof())
	{
		Score newScore;
		long num;
		input_file>>num;
		newScore.mScore.resize(M);
		for (int i=0;i<M;++i)
			input_file>>newScore.mScore[i];
		mSecondScore[num]=newScore;
	}
	input_file.close();
	cout<<"�����ɹ���"<<endl;
	system("pause");
	/*
	cout<<"�����ɹ�����������˳�....";
	getchar();
	getchar();*/
}

void Second::print()
{
	Student tStudent;
	cout<<"ѧ��     ����      �Ա�       ����       סַ"<<endl;
	for (it=mSecondScore.begin();it!=mSecondScore.end();++it)
	{
		tStudent=getStudentByNum(it->first);
		cout<<left<<setw(10)<<it->first;
		cout<<left<<setw(10)<<tStudent.mName;
		if (tStudent.mSex==0) cout<<left<<setw(10)<<"��";
		else cout<<left<<setw(10)<<"Ů";
		cout<<left<<setw(10)<<tStudent.mAge;
		cout<<left<<setw(10)<<tStudent.mAddr;
		cout<<endl;
	}
	cout<<endl;
	cout<<"��ѯ�ɹ���"<<endl;
	system("pause");
}

void Second::printScore()
{
	cout<<"ѧ��     ";
	for (int i=0;i<M;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;
	for (it=mSecondScore.begin();it!=mSecondScore.end();++it)
	{
		cout<<left<<setw(10)<<it->first;
		for (int j=0;j<M;++j)
			cout<<left<<setw(6)<<it->second.mScore[j];
		cout<<endl;
	}
	cout<<endl;
}

void Second::setScore()
{
	printScore();
	cout<<"�Ƿ��޸ĳɼ���y/n��:";
	char x;
	while (cin>>x && x!='y' && x!='n') cout<<"����������������룺";
	if (x=='y')
	{
		while (1)
		{
			long num;
			cout<<"��������Ҫ�޸���Ϣ��ѧ��ѧ��(����-1������һ��)��";
			while (cin>>num && mSecondScore.find(num)==mSecondScore.end() && num!=-1) cout<<"����������������룺";
			if (num==-1) return;
			while (1)
			{
				it=mSecondScore.find(num);
				cout<<"��������Ҫ�޸ĵĿ�Ŀ���(����-1����ѧ������)��";
				int n;
				while (cin>>n && (n<1 || n>M) && n!=-1) cout<<"����������������룺";
				if (n==-1) break;
				cout<<"�������޸ĺ�ĳɼ���";
				int score;
				cin>>score;
				it->second.mScore[n-1]=score;

				system("cls");
				printScore();
				cout<<"�޸ĳɹ�����ѡ�����:";
				cout<<"1. �����޸ı�ѧ��������Ŀ�ɼ�"<<endl;
				cout<<"2. �޸�����ѧ���ĳɼ�"<<endl;
				cout<<"3. ����"<<endl;
				cout<<"�����룺";
				while (cin>>n && (n<1 || n>3)) cout<<"����������������룺";
				if (n==1) continue;
				if (n==2) break;
				if (n==3) 
				{
					output();
					return;
				}
			}	
		}
	}
	if (x=='n') return;
}

void Second::good()		
{
	cout<<"�ɼ������ѧ����"<<endl;
	cout<<"ѧ��   ";
	for (int i=0;i<M;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;

	output_file.open("SecondGood.dat");
	int sum=0;
	for (it=mSecondScore.begin();it!=mSecondScore.end();++it)
	{
		int count=0,count2=0;
		for (int i=0;i<M;++i)
		{
			if (it->second.mScore[i]>=85) count++;
			if (it->second.mScore[i]>=70) count2++;
		}
		if (count>=3 && count2==M)
		{
			it->second.isGood=true;
			sum++;
			output_file<<left<<setw(8)<<it->first;
			cout<<left<<setw(8)<<it->first;
			for (int j=0;j<M;++j) 
			{
				output_file<<left<<setw(6)<<it->second.mScore[j];
				cout<<left<<setw(6)<<it->second.mScore[j];
			}
			output_file<<endl;
			cout<<endl;
		}
		else it->second.isGood=false;
	}
	output_file.close();
	if (sum==0) cout<<endl<<"�޳ɼ�����ѧ����"<<endl<<endl;
	cout<<endl;
	cout<<"ͳ����ɣ�"<<endl;
	system("pause");
	/*
	cout<<"ͳ����ɣ���������˳�....";
	getchar();
	getchar();*/
}

void Second::fail()	
{
	cout<<"��Ҫ������ѧ����"<<endl;
	cout<<"ѧ��   ";
	for (int i=0;i<M;++i) cout<<"��Ŀ"<<i+1<<" ";
	cout<<endl;

	output_file.open("SecondFail.dat");
	int sum=0;
	for (it=mSecondScore.begin();it!=mSecondScore.end();++it)
	{
		int count=0;
		for (int i=0;i<M;++i)
			if (it->second.mScore[i]<60) count++;
		if (count)
		{
			it->second.isFail=true;
			sum++;
			output_file<<left<<setw(8)<<it->first;
			cout<<left<<setw(8)<<it->first;
			for (int j=0;j<M;++j) 
			{
				output_file<<left<<setw(6)<<it->second.mScore[j];
				cout<<left<<setw(6)<<it->second.mScore[j];
			}
			output_file<<endl;
			cout<<endl;
		}
		else it->second.isFail=false;
	}
	output_file.close();
	if (sum==0) cout<<endl<<"����Ҫ������ѧ����"<<endl<<endl;
	cout<<endl;
	cout<<"ͳ����ɣ�"<<endl;
	system("pause");
	/*
	cout<<"ͳ����ɣ���������˳�....";
	getchar();
	getchar();*/
}

map<long,Score> First::getFirstScore()
{
	return mFirstScore;
}

map<long,Score> Second::getSecondScore()
{
	return mSecondScore;
}

void StudentMIS::selectOperation()
{
	int n;
	while (1)
	{
		system("cls");
		cout<<"��ӭѧλ��Ա��¼ϵͳ����ѡ���ܣ�"<<endl;
		cout<<"1. ��ѯѧ����Ϣ"<<endl;
		cout<<"2. ��ѯѧ���ɼ�"<<endl;
		cout<<"3. ͳ�ƻ��ѧλ����Ϣ"<<endl;
		cout<<"0. ����"<<endl;
		cout<<"������: ";
		while(cin>>n &&( n<0 || n>3)) cout<<"����������������룺 ";
		system("cls");
		if (n==1) print();
		if (n==2) printScore();
		if (n==3) degree();
		if (n==0) break;
	}
}

void First::printFirstNameByNum(long num)
{
	if (mFirstScore.find(num)!=mFirstScore.end()) cout<<setw(13)<<mMajorDepName;
	else cout<<"��";
}

void Second::printSecondNameByNum(long num)
{
	if (mSecondScore.find(num)!=mSecondScore.end()) cout<<setw(13)<<mSecondDepName;
	else cout<<"��";
}

void StudentMIS::print()
{
	map<long,Student> student=getStudent();
	map<long,Student>::iterator it;
	cout<<"ѧ��       ����    �Ա�      ����     סַ         ����רҵ     ����רҵ"<<endl;
	for (it=student.begin();it!=student.end();++it)
	{
		cout<<left<<setw(10)<<it->first;
		cout<<left<<setw(10)<<it->second.mName;
		if (it->second.mSex==0)	cout<<left<<setw(10)<<"��";
		else cout<<left<<setw(10)<<"Ů";
		cout<<left<<setw(8)<<it->second.mAge;
		cout<<left<<setw(15)<<it->second.mAddr;
		printFirstNameByNum(it->first);
		printSecondNameByNum(it->first);
		cout<<endl;
	}
	cout<<endl;
	cout<<"��ѯ�ɹ���"<<endl;
	system("pause");
	/*cout<<"�������������...";
	getchar();
	getchar();*/
}

void StudentMIS::printScore()
{
	cout<<"����רҵ�ɼ���"<<endl;
	First::printScore();
	cout<<endl;
	cout<<"����רҵ�ɼ�:"<<endl;
	Second::printScore();
	cout<<endl;
	cout<<"��ѯ�ɹ���"<<endl;
	system("pause");
	/*
	cout<<"�������������...";
	getchar();
	getchar();*/
}


void StudentMIS::degree()		
{
	map<long,Score>::iterator it;
	map<long,Score> firstScore=getFirstScore();
	map<long,Score> secondScore=getSecondScore();
	long tNum;
	Student tStudent;
	output_file.open("Degree.dat");

	cout<<"�������רҵѧλ��ѧ����"<<endl;
	cout<<"ѧ��     ����  �Ա� ����   סַ    ";
	output_file<<"�������רҵѧλ��ѧ����"<<endl;
	output_file<<"ѧ��     ����  �Ա� ����   סַ    ";
	for (int i=0;i<N;++i) 
	{
		cout<<"��Ŀ"<<i+1<<" ";
		output_file<<"��Ŀ"<<i+1<<" ";
	}
	cout<<endl;
	output_file<<endl;
	for (it=firstScore.begin();it!=firstScore.end();++it)
	{
		tNum=it->first;
		tStudent=getStudentByNum(tNum);
		if (!it->second.isFail)
		{
			output_file<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName<<setw(4)<<tStudent.mSex<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			cout<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName;
			if (tStudent.mSex==0) cout<<setw(4)<<"��";
			else cout<<setw(4)<<"Ů";
			cout<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			for (int i=0;i<N;++i) 
			{
				cout<<setw(6)<<it->second.mScore[i];
				output_file<<setw(6)<<it->second.mScore[i];
			}
			cout<<endl;
			output_file<<endl;
		}
	}
	cout<<endl;
	output_file<<endl;

	cout<<"��ø���רҵѧλ��ѧ����"<<endl;
	cout<<"ѧ��     ����  �Ա� ����   סַ    ";
	output_file<<"�������רҵѧλ��ѧ����"<<endl;
	output_file<<"ѧ��     ����  �Ա� ����   סַ    ";
	for (int i=0;i<M;++i) 
	{
		cout<<"��Ŀ"<<i+1<<" ";
		output_file<<"��Ŀ"<<i+1<<" ";
	}
	cout<<endl;
	output_file<<endl;
	for (it=secondScore.begin();it!=secondScore.end();++it)
	{
		tNum=it->first;
		tStudent=getStudentByNum(tNum);
		if (!firstScore[tNum].isFail && !it->second.isFail)
		{
			output_file<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName<<setw(4)<<tStudent.mSex<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			cout<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName;
			if (tStudent.mSex==0) cout<<setw(4)<<"��";
			else cout<<setw(4)<<"Ů";
			cout<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			for (int i=0;i<M;++i) 
			{
				cout<<setw(6)<<it->second.mScore[i];
				output_file<<setw(6)<<it->second.mScore[i];
			}
			cout<<endl;
			output_file<<endl;
		}
	}
	cout<<endl;
	output_file<<endl;

	cout<<"���ܻ������רҵѧλ��ѧ����"<<endl;
	cout<<"ѧ��     ����  �Ա� ����   סַ    ";
	output_file<<"�������רҵѧλ��ѧ����"<<endl;
	output_file<<"ѧ��     ����      �Ա�       ����       סַ";
	for (int i=0;i<N;++i) 
	{
		cout<<"��Ŀ"<<i+1<<" ";
		output_file<<"��Ŀ"<<i+1<<" ";
	}
	cout<<endl;
	output_file<<endl;
	for (it=firstScore.begin();it!=firstScore.end();++it)
	{
		tNum=it->first;
		tStudent=getStudentByNum(tNum);
		if (it->second.isFail)
		{
			output_file<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName<<setw(4)<<tStudent.mSex<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			cout<<left<<setw(8)<<tNum<<setw(8)<<tStudent.mName;
			if (tStudent.mSex==0) cout<<setw(4)<<"��";
			else cout<<setw(4)<<"Ů";
			cout<<setw(5)<<tStudent.mAge<<setw(11)<<tStudent.mAddr;
			for (int i=0;i<N;++i) 
			{
				cout<<setw(6)<<it->second.mScore[i];
				output_file<<setw(6)<<it->second.mScore[i];
			}
			cout<<endl;
			output_file<<endl;
		}
	}
	cout<<endl;
	output_file<<endl;

	//cout<<"ͳ����ɣ���������˳�....";
	cout<<"ͳ����ɣ�"<<endl;
	system("pause");
	/*
	getchar();
	getchar();*/
}
