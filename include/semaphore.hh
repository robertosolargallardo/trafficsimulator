#ifndef __SEMAPHORE__HH__
#define __SEMAPHORE__HH__
#include <random>
#define THRESHOLD 5.0

class semaphore{
	public:	int _state;
				double _accum;

	public:	semaphore(void);
				semaphore(const semaphore&);
				semaphore& operator=(const semaphore&);
				~semaphore(void);
	
				void update(void);
				int state(void) const;
	
};
#endif
