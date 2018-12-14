#ifndef __CAR__HH__
#define __CAR__HH__
#include <utility>

class car
{
private:
    double _position;
    std::pair<int,int> _location;

public:
    car(void);
    car(const car&);
    car& operator=(const car&);
    ~car(void);

    car(const std::pair<int,int>&);

    std::pair<int,int> location(void) const;
    void location(const std::pair<int,int>&);

    double position(void) const;
    void position(const double&);

};
#endif
