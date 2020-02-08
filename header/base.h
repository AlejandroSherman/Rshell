#ifndef __BASE_H__
#define __BASE_H__

using namespace std;
#include <string>
#include <vector>
class Base {
    public:
        /* Constructor */
        Base() { };

	vector<string> parsing(string);
        /* Virtual Functions */
        virtual bool execute() = 0;
};

#endif
