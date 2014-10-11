#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;

class Particle
{
	private:
		vector<int> myLocation;
	public:
		vector<int> getLocation() { return myLocation; };
		void setLocation( vector<int> newLocation ) {
			myLocation = newLocation;
		};

		Particle();
		~Particle();
};

Particle::Particle() {
	vector<int> ranLocation(3);
	int nRand;
	clock_t t;
	t = clock();
	srand( t );
	
	for ( int i = 0; i < 3; i++ ) {
		nRand = rand() % INT_MAX;
		ranLocation[i] = nRand;
	}

	myLocation = ranLocation;
}

Particle::~Particle() {
}
