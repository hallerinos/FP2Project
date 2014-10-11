#include <iostream>
#include <list>
#include <fstream>
#include <sys/time.h>
#include "Coordinate.hpp"

using namespace std;

void printLocations( list<Coordinate>, string );
list<Coordinate> addStepwise( list<Coordinate> coords);

int main()
{
	struct timeval start, end;
	gettimeofday( &start, NULL );
	srand ( 1 );
	list<Coordinate> coords;
	for ( long i = 0; i < 1000; i++ ) {
		Coordinate newCoord( 'r' );
		coords.push_back( newCoord );
	}
	printLocations( coords , "Locations.txt" );
	printLocations( addStepwise( coords ), "Walk.txt" );
	
	gettimeofday( &end, NULL );
	cout << (float)(( end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec ) / 1000000;	
	return 0;
}

list<Coordinate> addStepwise( list<Coordinate> coords ) {
	list<Coordinate> sum;
	list<Coordinate>::iterator itPart = coords.begin();
	
	sum.push_back( *itPart );

	while ( itPart != coords.end() ) {
		vector<int> loc1;
		vector<int> loc2;
		loc1 = itPart->getLocation();
		itPart++;
		if ( itPart == coords.end() ) return sum;
		loc2 = itPart->getLocation();
		for ( unsigned i = 0; i<loc1.size(); i++ ) {
			loc1[i] += loc2[i];
		}
		Coordinate walk( loc1 );
		sum.push_back( walk );
	}
	return sum;
}

void printLocations( list<Coordinate> coords , string filename ) {
	// open file stream
	ofstream myfile;
	myfile.open( filename );
	// particle iterator
	list<Coordinate>::iterator itPart = coords.begin();
	myfile << "X";
	myfile << "\tY";
	myfile << "\tZ\n";
	while( itPart != coords.end() ) {
		vector<int> location = itPart->getLocation();
		myfile << "" << location[0];
		myfile << "\t" <<	location[1]; 
		myfile << "\t" << location[2] << "\n";
		itPart++;
	}
	myfile.close();
}
