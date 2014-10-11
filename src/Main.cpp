#include <iostream>
#include <list>
#include <fstream>
#include "Particles.hpp"

using namespace std;

void printLocations( list<Particle> );

int main()
{
	list<Particle> particles;
	for ( int i = 0; i < 5; i++ ) {
		Particle newPart;
		particles.push_back( newPart );
	}

	printLocations( particles );
	
	return 0;
}

void printLocations( list<Particle> particles ) {
	// open file stream
	ofstream myfile;
	myfile.open( "ParticleLocations.txt" );
	// particle iterator
	list<Particle>::iterator itPart = particles.begin();
	myfile << "    X";
	myfile << "\t\t    Y";
	myfile << "\t\t    Z\n";
	while( itPart != particles.end() ) {
		myfile << "" << itPart->getLocation()[0];
		myfile << "\t" << itPart->getLocation()[1];
		myfile << "\t" << itPart->getLocation()[2] << "\n";
		itPart++;
	}
	myfile.close();
}
