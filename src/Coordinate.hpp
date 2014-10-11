#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;

class Coordinate
{
	private:
		vector<int> myLocation;
	public:
		vector<int> getLocation() { return myLocation; };
		void setLocation( vector<int> newLocation ) {
			myLocation = newLocation;
		};

		Coordinate( char );
		Coordinate( vector<int> );
		~Coordinate();
};

Coordinate::Coordinate( char ini ) {
	if ( ini == 'r' ) { 
		vector<int> ranLocation(3);
		int nRand;

		for ( int i = 0; i < 3; i++ ) {
			nRand = rand() % 100-50;
			ranLocation[i] = nRand;
		}

		myLocation = ranLocation;
	}
}

Coordinate::Coordinate( vector<int> newLocation ) {
	myLocation = newLocation;
}

Coordinate::~Coordinate() {
}
