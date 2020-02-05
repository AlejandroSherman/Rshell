#include "../header/base.h"
#include "../header/and.h"
#include<iostream>
#include<string>
using namespace std;

int main()
{
	cout <<"guest@rshell:~$ ";
	string userinput;
	getline(cin,userinput);
	Base *input = new And();

	input->parsing(userinput);
	return 0;
}
