#include <time.h>



class Timer
{
	public:
	void start();
	void stop();
	double time();
	Timer();
	private:
	clock_t start_t,stop_t;

};

void Timer::start()
{start_t=clock();}

void Timer::stop()
{stop_t=clock();}

double Timer::time()
{return stop_t-start_t;}

Timer::Timer() {}