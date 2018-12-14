#ifndef __STREET__HH__
#define __STREET__HH__
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

class street
{
private:
    int _capacity;
    std::vector<int> _cars;

public:
    street(void);
    street(const street&);
    street& operator=(const street&);
    ~street(void);

    street(const int&);

    void add(const int&);
    void del(const int&);
    bool full(void);

    std::vector<int> cars(void) const;
};
#endif
