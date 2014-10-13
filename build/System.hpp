#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <tgmath.h>

using namespace std;

class System {
	public:
		// Con- and Destructor
		System( int numPart, int dimSys );
		~System();
		// Methods
		//int GetEnergy();
		//int McStep();
		//int MdStep();
		// Getter
		int GetCoordinate( int partNumber, int axis ) const;
		double GetDistance( int coordOne, int coordTwo) const;
		void PrintCoordinates() const;
	private:	
		int numberOfParticles, dimOfSystem;
		int *coords;
};

/*--------------------------------------------------------------------
 * Constructor that initialises n*D random coordinates
 *------------------------------------------------------------------*/
System::System( int newNumberOfParticles, int newDimOfSystem ) {
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;

	coords = new int[ numberOfParticles * dimOfSystem ];
	// cout << "These are the " << numberOfParticles 
	// << " Particles:" << endl;
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	{
			(coords)[i*dimOfSystem + j] = rand() % 101 - 50;
			// cout << "Particle: " << i << " Axis: " << j << ": \t" 
			// << (coords)[i*dimOfSystem + j] << "\t" << endl;
		}
	cout << endl;
}

System::~System() { 
	delete coords;
	cout << "Destructor call." << endl; 
}

int System::GetCoordinate ( int partNumber, int axis) const {
	return (coords)[partNumber*dimOfSystem + axis];
}

/*--------------------------------------------------------------------
 * Print Coordinates to a *.txt file
 *------------------------------------------------------------------*/
void System::PrintCoordinates() const {
	ofstream file;
	file.open( "InitialCoords.txt" );
	file << "Initial coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numberOfParticles; i++ ) {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			file << coords[i*dimOfSystem + j] << "\t";
		}
		file << endl;
	}
	file.close();
}

/*--------------------------------------------------------------------
 * Calculate relative distances 
 *------------------------------------------------------------------*/
double System::GetDistance( int coordOne, int coordTwo ) const {
	double dist = 0;
	for ( int j = 0; j < dimOfSystem; j++ ) {
		dist += pow( coords[ coordOne*dimOfSystem + j] -
			 coords[ coordTwo*dimOfSystem + j], 2 );
	}
	return sqrt(dist);
}
