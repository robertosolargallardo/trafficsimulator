#include <semaphore.hh>
semaphore::semaphore(void)
{
    static std::random_device seed;
    static std::mt19937 rng(seed());
    static std::uniform_int_distribution<int> uniform(0,1);
    this->_state=uniform(rng);
}
semaphore::semaphore(const semaphore &_sem)
{
    this->_state=_sem._state;
    this->_accum=_sem._accum;
}
semaphore& semaphore::operator=(const semaphore &_sem)
{
    this->_state=_sem._state;
    this->_accum=_sem._accum;
    return(*this);
}
semaphore::~semaphore(void)
{

}
void semaphore::update(void)
{
    static std::random_device seed;
    static std::mt19937 rng(seed());
    static std::uniform_real_distribution<double> uniform(0.0,1.0);

    this->_accum+=uniform(rng);
    if(this->_accum>THRESHOLD)
        {
            ++this->_state%=2;
            this->_accum=0.0;
        }
}
int semaphore::state(void) const
{
    return(this->_state);
}
