#ifndef __BASE_H__
#define __BASE_H__

using namespace std;
#include <string>
class Base {
    public:
        /* Constructor */
        Base() { };

	void parsing(string);
        /* Virtual Functions */
        virtual bool execute(string) = 0;
};

#endif
