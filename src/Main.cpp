#include <iostream>
#include <list>
#include <fstream>
#include "Coordinate.hpp"

using namespace std;

void printLocations( list<Coordinate> );
list<Coordinate> addStepwise( list<Coordinate> coords );

int main()
{
	srand ( time (NULL) );
	list<Coordinate> coords;
	for ( long i = 0; i < 100000; i++ ) {
		Coordinate newCoord( 'r' );
		coords.push_back( newCoord );
	}
	
//	printLocations( coords );
//	printLocations( addStepwise( coords ) );
	return 0;
}

list<Coordinate> addStepwise( list<Coordinate> coords ) {
	list<Coordinate> sum;
	list<Coordinate>::iterator itPart = coords.begin();
	
	sum.push_back( *itPart );

	while ( itPart != coords.end() ) {
		vector<int> loc1(3);
		vector<int> loc2(3);
		loc1 = itPart->getLocation();
		itPart++;
		loc2 = itPart->getLocation();
		for ( unsigned i = 0; i<3; i++ ) {
			loc1[i] = loc1[i] + loc2[i];
		}
		Coordinate walk( loc1 );
		sum.push_back( loc1 );
	}

	return sum;
}

void printLocations( list<Coordinate> coords ) {
	// open file stream
	ofstream myfile;
	myfile.open( "Locations.txt" );
	// particle iterator
	list<Coordinate>::iterator itPart = coords.begin();
	myfile << "X";
	myfile << "\tY";
	myfile << "\tZ\n";
	while( itPart != coords.end() ) {
		myfile << "" << itPart->getLocation()[0];
		myfile << "\t" << itPart->getLocation()[1];
		myfile << "\t" << itPart->getLocation()[2] << "\n";
		itPart++;
	}
	myfile.close();
}
