#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include <string>

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
		int GetCoordinate( int partNumber, int axis );
	private:	
		int numberOfParticles, dimOfSystem;
		int *coords;
};

System::System( int newNumberOfParticles, int newDimOfSystem ) {
	numberOfParticles = newNumberOfParticles;
	dimOfSystem = newDimOfSystem;

	coords = new int[ numberOfParticles * dimOfSystem ];
	cout << "These are the " << numberOfParticles << " Particles:" << endl;
	for ( int i = 0; i < numberOfParticles; i++)
 		for ( int j = 0; j < dimOfSystem; j++ )	{
			(coords)[i*dimOfSystem + j] = rand() % 101 - 50;
			cout << "Particle: " << i << " Axis: " << j << ": \t" 
				<< (coords)[i*dimOfSystem + j] << "\t" << endl;
		}
	cout << endl;
}

System::~System() { 
	delete coords;
	cout << "Destructor call." << endl; 
}

int System::GetCoordinate ( int partNumber, int axis) {
	return (coords)[partNumber*dimOfSystem + axis];
}

int main()
{
	// initialise random seed	
	// srand( time(NULL) );		// different seeds
	srand( 0 );								// same seed 

	// measuring the calculation time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	
	/*--------------------------------------------------------------------
	 * Read system settings from input file
	 *------------------------------------------------------------------*/
	int numOfParticles=0, dimOfSystem=0;
	
	ifstream inputFile("SystemSpecs.txt");
	string line;
	getline( inputFile, line ); cout << line << endl;
	getline( inputFile, line ); cout << line << endl;
	getline( inputFile, line ); cout << line << endl;
	if ( inputFile.is_open() ) {
		getline( inputFile, line ); cout << line << " ";
		getline( inputFile, line );
		cout << (numOfParticles = atoi( line.c_str() )) << endl;
		
		getline( inputFile, line ); cout << line << " "; 
		getline( inputFile, line );
		cout << ( dimOfSystem = atoi( line.c_str() ) ) << endl;
		
		inputFile.close();
	}

	System MC( numOfParticles, dimOfSystem );
	for ( int j = 0; j < dimOfSystem; j++) {
		cout << "Axis " << j << " :" << MC.GetCoordinate(1, j) << endl;
	}
	



	/*--------------------------------------------------------------------
	 * Print Coordinates to a *.txt file
	 *------------------------------------------------------------------
	ofstream file;
	file.open( "InitialCoords.txt" );
	file << "Initial coordinates" << endl;
	file << "X\tY\tZ" << endl;
	for ( int i = 0; i < numOfParticles; i++ ) {
		for ( int j = 0; j < dimOfSystem; j++ ) {
			file << parts[i*dimOfSystem + j] << "\t";
		}
		file << endl;
	}
	file.close();*/
		
	/*--------------------------------------------------------------------
	 * Calculate relative distances 
	 *------------------------------------------------------------------*/
	
	/*--------------------------------------------------------------------
	 * Calculate energy 
	 *------------------------------------------------------------------*/
	
	/*--------------------------------------------------------------------
	 * Make trial state
	 *------------------------------------------------------------------*/
	gettimeofday(&end, NULL);
	cout << "Time needed to create System: " 
		<< ( (end.tv_sec  - start.tv_sec )*1000000 + 
				  end.tv_usec - start.tv_usec ) / 1000000. << endl;
	return 0;
}


