#ifndef __SIMULATOR__H__
#define __SIMULATOR__H__
#include <map>
#include <random>
#include <iostream>
#include <car.hh>
#include <street.hh>
#include <semaphore.hh>

class simulator
{
private:
    int _capacity;
    int _size;
    int _n;
    int _m;
    std::map<int,car> _cars;
    std::map<std::pair<int,int>,street> _streets;
    std::map<std::pair<int,int>,semaphore> _semaphores;

public:
    simulator(void);
    simulator(const simulator&);
    simulator& operator=(const simulator&);
    ~simulator(void);

    simulator(const int&,const int&,const int&);

    void run(void);
    void show(void);

    void move(const int&,const std::pair<int,int>&,const std::pair<int,int>&);
};
#endif
