#ifndef __BASE_H__
#define __BASE_H__

using namespace std;
#include <string>
#include <vector>
#include <iostream>
class Base {
    public:
        /* Constructor */
        Base() { };

	vector<string> parsing(string);
        /* Virtual Functions */
        virtual bool execute() = 0;
        virtual string getPath() = 0; 
        virtual void print() {};
        virtual vector<string> getVector() {};
};

#endif
