#ifndef __BASE_H__
#define __BASE_H__


class Base {
    public:
        /* Constructor */
        Base() { };

        /* Virtual Functions */
        virtual bool execute() = 0;
        virtual void parse() { }
};

#endif
