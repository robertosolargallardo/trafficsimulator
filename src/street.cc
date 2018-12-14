#include <street.hh>
street::street(void)
{

}
street::street(const street &_str)
{
    this->_capacity=_str._capacity;
    this->_cars=_str._cars;
}
street& street::operator=(const street &_str)
{
    this->_capacity=_str._capacity;
    this->_cars=_str._cars;
    return(*this);
}
street::~street(void)
{

}
street::street(const int &_capacity)
{
    this->_capacity=_capacity;
}
void street::add(const int &_id)
{
    this->_cars.push_back(_id);
}
void street::del(const int &_id)
{
    this->_cars.erase(std::find(this->_cars.begin(),this->_cars.end(),_id));
}
bool street::full(void)
{
    return(this->_cars.size()>=this->_capacity);
}
std::vector<int> street::cars(void) const
{
    return(this->_cars);
}
