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


	vector <string> tokens = (input->parsing(userinput));
	cout << "Size of tokens vector is: " << tokens.size() << endl;
	cout << "Contents of tokens vector are:" << endl;
	for (int i = 0; i < tokens.size(); ++i){
		cout << tokens.at(i) << endl;
	}
	return 0;
}
