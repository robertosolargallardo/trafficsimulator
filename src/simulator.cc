#include <simulator.hh>
simulator::simulator(void)
{

}
simulator::simulator(const simulator &_sim)
{

}
simulator& simulator::operator=(const simulator &_sim)
{
    return(*this);
}
simulator::~simulator(void)
{

}
simulator::simulator(const int &_size,const int &_capacity,const int &_ncars)
{
    this->_capacity=_capacity;
    this->_size=_size;

    this->_n=_size/_capacity;
    this->_m=2*this->_n+1;

    for(int i=0; i<this->_n; ++i)
        for(int j=0; j<this->_n; ++j)
            {
                this->_semaphores[std::make_pair(i,j)]=semaphore();
            }

    int gap=1;
    for(int i=0; i<this->_m; ++i)
        {
            for(int j=gap; j<this->_m; j+=2)
                {
                    if(i!=j)
                        this->_streets[std::make_pair(i,j)]=street(_capacity);
                }
            ++gap%=2;
        }

    static std::random_device seed;
    static std::mt19937 rng(seed());
    static std::uniform_int_distribution<int> uniform(0,this->_streets.size()-1);

    for(int i=0; i<_ncars; ++i)
        {
            std::pair<int,int> location;
            do
                {
                    auto it=this->_streets.begin();
                    std::advance(it,uniform(rng));
                    location=it->first;
                }
            while (this->_streets[location].full());

            this->_cars[i]=car(location);
            this->_streets[location].add(i);
        }
}
void simulator::run(void)
{
    static std::random_device seed;
    static std::mt19937 rng(seed());
    static std::uniform_real_distribution<double> speed(0.0,2.0);

    for(int i=0; i<this->_semaphores.size(); ++i)
        {
            auto it=this->_semaphores.begin();
            std::advance(it,i);
            it->second.update();
        }

    for(int i=0; i<this->_streets.size(); ++i)
        {
            auto it=this->_streets.begin();
            std::advance(it,i);

            for(int j=0; j<it->second.cars().size(); ++j)
                {
                    int id=it->second.cars()[j];
                    this->_cars[id].position(this->_cars[id].position()+speed(rng));

                    if(this->_cars[id].position()>this->_capacity)
                        {
                            std::pair<int,int> src=this->_cars[id].location();
                            if(src.first%2==0)
                                {
                                    if(src.second%4==1)
                                        {
                                            //std::cout << "arr->abj" << std::endl;
                                            if(src.first==(this->_m-1))
                                                {
                                                    //std::cout << "extremo abajo" << std::endl;
                                                    auto dst=std::make_pair(0,src.second);
                                                    this->move(id,src,dst);
                                                }
                                            else
                                                {
                                                    auto k=std::make_pair((src.first+1)/2,(src.second)/2);
                                                    if(this->_semaphores[k].state())
                                                        {
                                                            auto dst=std::make_pair(src.first+2,src.second);
                                                            this->move(id,src,dst);
                                                        }
                                                    else
                                                        this->_cars[id].position(double(this->_capacity));
                                                }
                                        }
                                    else if(src.second%4==3)
                                        {
                                            //std::cout << "abj->arr" << std::endl;
                                            if(src.first==0)
                                                {
                                                    //std::cout << "extremo arriba" << std::endl;
                                                    auto dst=std::make_pair(this->_m-1,src.second);
                                                    this->move(id,src,dst);
                                                }
                                            else
                                                {
                                                    auto k=std::make_pair((src.first-1)/2,(src.second)/2);
                                                    if(this->_semaphores[k].state())
                                                        {
                                                            auto dst=std::make_pair(src.first-2,src.second);
                                                            this->move(id,src,dst);
                                                        }
                                                    else
                                                        this->_cars[id].position(double(this->_capacity));
                                                }

                                        }
                                }
                            else
                                {
                                    if(src.first%4==1)
                                        {
                                            //std::cout << "izq->der" << std::endl;
                                            if(src.second==(this->_m-1))
                                                {
                                                    //std::cout << "extremo der" << std::endl;
                                                    auto dst=std::make_pair(src.first,0);
                                                    this->move(id,src,dst);
                                                }
                                            else
                                                {
                                                    auto k=std::make_pair((src.first)/2,(src.second+1)/2);
                                                    if(this->_semaphores[k].state())
                                                        {
                                                            auto dst=std::make_pair(src.first,src.second+2);
                                                            this->move(id,src,dst);
                                                        }
                                                    else
                                                        this->_cars[id].position(double(this->_capacity));
                                                }
                                        }
                                    if(src.first%4==3)
                                        {
                                            //std::cout << "der->izq" << std::endl;
                                            if(src.second==0)
                                                {
                                                    //std::cout << "extremo izq" << std::endl;
                                                    auto dst=std::make_pair(src.first,this->_m-1);
                                                    this->move(id,src,dst);
                                                }
                                            else
                                                {
                                                    auto k=std::make_pair((src.first)/2,(src.second-1)/2);
                                                    if(this->_semaphores[k].state())
                                                        {
                                                            auto dst=std::make_pair(src.first,src.second-2);
                                                            this->move(id,src,dst);
                                                        }
                                                    else
                                                        this->_cars[id].position(double(this->_capacity));
                                                }
                                        }
                                }
                        }
                }
        }
}

void simulator::move(const int &_id,const std::pair<int,int> &_src,const std::pair<int,int> &_dst)
{
    if(!this->_streets[_dst].full())
        {
            //std::cout << "hay espacio" << std::endl;
            this->_streets[_src].del(_id);
            this->_streets[_dst].add(_id);
            this->_cars[_id].position(this->_cars[_id].position()-double(this->_capacity));
            this->_cars[_id].location(_dst);
        }
    else
        this->_cars[_id].position(double(this->_capacity));
}

void simulator::show(void)
{
    for(int i=0; i<this->_m; ++i)
        {
            for(int j=0; j<this->_m; ++j)
                {
                    if((i%2==0 && j%2==1) || (i%2==1 && j%2==0))
                        std::cout << "(" << this->_streets[std::make_pair(i,j)].cars().size() << ") ";
                    else if(i%2==1 && j%2==1)
                        std::cout << "<" << this->_semaphores[std::make_pair(i/2,j/2)].state() << "> ";
                    else
                        std::cout << "[0] ";
                }
            std::cout << std::endl;
        }
}
