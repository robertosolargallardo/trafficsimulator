#include <iostream>
#include <unistd.h>
#include <simulator.hh>

int main(int argc,char **argv){
	int size=-1;
	int iterations=-1;
	int nthreads=-1;
	int ncars=-1;
	int capacity=-1;
	char c;

	while((c=getopt(argc,argv,"s:i:t:n:c:"))!=-1) {
        switch(c) {
        case 's': {
            size=std::stoi(optarg);
            break;
        }
        case 'i': {
            iterations=std::stoi(optarg);
            break;
        }
        case 't': {
            nthreads=std::stoi(optarg);
            break;
        }
        case 'n': {
            ncars=std::stoi(optarg);
            break;
        }
        case 'c': {
            capacity=std::stoi(optarg);
            break;
        }
        default: {
				std::cerr << "error::unknown parameter \"" << c << "\"" << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
        }
   }

	simulator sim(size,capacity,ncars);
	
	for(int i=0;i<iterations;++i){
		sim.run();
		printf("\033c");
		sim.show();
		sleep(1);
	}

	return(0);
}
