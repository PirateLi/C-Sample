#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
using namespace std;

#define N 5
#define M 4

class Student
{
public:
	char mName[20];
	int mSex;
	int mAge;
	char mAddr[30];
};

class Score
{
public:
	vector<int> mScore;		
	bool isGood;
	bool isFail;
};

class StudentBase
{
private:
	map<long,Student> student;
	map<long,Student>::iterator it;
//	string password;		//只有一个对象，所以只有一个password

public:
	//StudentBase(){inputPassword();}		
	//void inputPassword();	
	void print();
	//void logIn();
	//string inPassword();
	Student getStudentByNum(long num);
	map<long,Student> getStudent();	
	void setStudent();
	void input();
	void output();
	void selectOperation();
};

class First:public virtual StudentBase
{
private:
	char mMajorDepName[30];
	map<long,Score> mFirstScore;
	map<long,Score>::iterator it;
	//string password;

	StudentBase::setStudent;

public:
	First();
	//void logIn();
	void print();
	void printScore();
	void output();
	void input();
	void printFirstNameByNum(long num);	
	map<long,Score> getFirstScore();	
	void setScore();
	void good();
	void fail();
	void selectOperation();


};

class Second:public virtual StudentBase
{
private:
	char mSecondDepName[30];
	map<long,Score> mSecondScore;
	map<long,Score>::iterator it;
	//string password;

	StudentBase::setStudent;

public:
	Second();
	//void logIn();
	void print();
	void printScore();
	void input();
	void output();
	void printSecondNameByNum(long num);
	map<long,Score> getSecondScore();	
	void setScore();
	void good();
	void fail();
	void selectOperation();
};

class StudentMIS:public First, public Second
{
private:
	First::setScore;
	Second::setScore;
	StudentBase::setStudent;
	//string password;

public:
	//StudentMIS(){inputPassword();}
	//void logIn();
	void print();
	void printScore();
	void degree();
	void selectOperation();
};


#endif