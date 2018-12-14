#include <car.hh>
car::car(void){

}
car::car(const car &_car){
	this->_location=_car._location;
	this->_position=_car._position;
}
car& car::operator=(const car &_car){
	this->_location=_car._location;
	this->_position=_car._position;
	return(*this);
}
car::~car(void){

}
car::car(const std::pair<int,int> &_location){
	this->_location=_location;
	this->_position=0.0;
}
std::pair<int,int> car::location(void) const{
	return(this->_location);
}
void car::location(const std::pair<int,int> &_location){
	this->_location=_location;
}
double car::position(void) const{
	return(this->_position);
}
void car::position(const double &_position){
	this->_position=_position;
}
