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

		Coordinate();
		Coordinate( vector<int> );
		~Coordinate();
};

Coordinate::Coordinate() {
	vector<int> ranLocation;
	int nRand;

	for ( int i = 0; i < 3; i++ ) {
		nRand = rand() % 100-50;
		ranLocation.push_back( nRand );
	}

	myLocation = ranLocation;
}

Coordinate::Coordinate( vector<int> newLocation ) {
	myLocation = newLocation;
}

Coordinate::~Coordinate() {
}
