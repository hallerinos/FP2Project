#include <iostream>
#include <list>
#include <fstream>
#include "Coordinate.hpp"

using namespace std;

void printLocations( list<Coordinate> );

int main()
{
	srand ( time (NULL) );
	list<Coordinate> coords;
	for ( int i = 0; i < 10000; i++ ) {
		Coordinate newCoord( 'r' );
		coords.push_back( newCoord );
	}
	printLocations( coords );
	
	return 0;
}

void printLocations( list<Coordinate> coords) {
	// open file stream
	ofstream myfile;
	myfile.open( "Locations.txt" );
	// particle iterator
	list<Coordinate>::iterator itPart = coords.begin();
	myfile << "    X";
	myfile << "\t\t    Y";
	myfile << "\t\t    Z\n";
	while( itPart != coords.end() ) {
		myfile << "" << itPart->getLocation()[0];
		myfile << "\t" << itPart->getLocation()[1];
		myfile << "\t" << itPart->getLocation()[2] << "\n";
		itPart++;
	}
	myfile.close();
}
