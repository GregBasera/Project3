/*
	BASERA, GREG EMERSON A.
	ICST201 N2
	8.25.17
	P3
	
	DESCRIPTION: Single-Digit Postfix Expression Solver
	
	-----------------------
	
	ALGORITHM:
	
	1. get expression (string) from user
	2. analyze wheather the expression is valid or not
		if first or second character is integer operation
			return false
		if (number of integer operation + 1) != (number of integers)
			return false
		if foreign character is present in string
			return false
		else return true
	3. store expression in txt file
	4. solve the expression and manages the stack
		read the txt file and string
		if string character isdigit
			push
		if string character = integer operands
			pop two values from stack
			do indicated operand on two values
			push result on stack
	5. displays the stack
		ideally, stack should be down to its last element
		pop the last element
*/

#include <iostream>
#include <fstream>
using namespace std;

class Postfix
{
	private:
		string str;
		int cap;		//abstract upperlimmit
		int stack[];	//no upperlimmit
		int topInd;
		ofstream write;
		ifstream read;
	public:
		Postfix();
		~Postfix();
		void getstr();			//get expression from user
		bool constraints();		//analyze wheather expression is valid
		void storefnl();		//store expression in txt file (string != int)
		void operate();			//solves the expression and manages the stack
		void display();			//displays the stack
		//Stack Essential Functions
		void push(int val);
		void pop();
		int top();
};

//#############################################################

Postfix::Postfix()
{
	topInd = 0;
}

Postfix::~Postfix()
{
	system("rm postfix.txt");	//deletes txt file immidiately after code stops
}

void Postfix::getstr()
{
	cout << "Enter Posfix expression (exclude spaces pls.): ";
	cin >> str;
	
	cap = str.length();
}

bool Postfix::constraints()
{
	//postfix do not have integer operation in the first 2 characters
	if(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/'){
		cout << "ERROR: Operation in first charater...\n\n";
		return false;
	}
	if(str[1] == '+' || str[1] == '-' || str[1] == '*' || str[1] == '/'){
		cout << "ERROR: Operation in second charater...\n\n";
		return false;
	}
	
	//postfix should have n integer operations and n+1 integers
	int num=0, sym=0;
	for(int q=0; q<cap; q++){
		if(str[q] == '+' || str[q] == '-' || str[q] == '*' || str[q] == '/'){
			sym++;
		}
		else if(isdigit(str[q])){
			num++;
		}
		else{
			cout << "ERROR: Foreign character in the expression...\n\n";	//also checks for foreign character
			return false;
		}
	}
	if((sym+1) != (num)){
		cout << "ERROR: Check the expression...\n\n";
		return false;
	}
	else{
		return true;	//if postfix expression from user is valid
	}
}

void Postfix::storefnl()
{
	//store final acceptable expression
	write.open("postfix.txt");
	for(int q=0; q<str.length(); q++){
		write << str[q] << endl;
	}
	write.close();
}

void Postfix::push(int val)
{
	if(topInd < cap-1){
		topInd++;
		stack[topInd] = val;
	}
	else{
		cout << "Stack is/was FULL ----- can't push()";
	}
}

void Postfix::pop()
{
	if(topInd >= 1){
		topInd--;
	}
	else{
		cout << "Stack is EMPTY ----- can't pop()";
	}
}

int Postfix::top()
{
	if(topInd >= 1){
		return (stack[topInd]);
	}
	else{
		cout << "Stack is EMPTY ----- can't return top(); returning '0'";
		return 0;
	}
}

void Postfix::operate()
{
	read.open("postfix.txt");
	int g;	//read an integer from file
	char b;	//read a character from file
	int greg, base, ra;
	for(int q=0; q<cap; q++){
		cout << "Token: " << str[q];
		if(isdigit(str[q])){
			read >> g;
			cout << "\tPush(" << g << ")";
			push(g);	//numbers. stack. should. only.
		}
		else{
			cout << "\tPop(" << top() << ")";
			greg = top();	//stack. top.
			pop();	//erase
			cout << "\tPop(" << top() << ")";
			base = top();	//stack. top.
			pop();	//erase
			if(str[q] == '+'){
				ra = greg + base;	//ALLA
			}
			if(str[q] == '-'){
				ra = base - greg;	//HU
			}
			if(str[q] == '*'){
				ra = greg * base;	//AK
			}
			if(str[q] == '/'){
				ra = base / greg;	//BAR
			}
			cout << "\tPush(" << ra << ")";
			push(ra);	//BOOM!
			
			read >> b;
		}
		cout << endl;
	}
	read.close();
}

void Postfix::display()
{
	cout << "\tPop(" << top() << ")";
	pop();
}

//#############################################################

int main()
{
	Postfix pls;
	
	do{
		pls.getstr();
	}while(!pls.constraints());	//no. stop. correct. expression.
	pls.storefnl();
	pls.operate();
	cout << endl << "Answer: ";
	pls.display();
	
	return 0;
}
