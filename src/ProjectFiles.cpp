#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

class System {
	public:
		// Con- and Destructor
		System( int numPart );
		~System();
		// Methods
		//int GetEnergy();
		//int McStep();
		//int MdStep();
		// Getter
		int GetCoordinate( int partNumber, int axis );
	private:	
		int n;
		int *pCoords[][3];
};

System::System( int numberOfParticles ) {
	n = numberOfParticles;
	pCoords = new int[n][3];
	cout << "These are the " << n << " Particles:" << endl;
	for ( int i = 0; i < n; i++) {
		(*pCoords)[i][0] = rand() % 101 - 50;
		(*pCoords)[i][1] = rand() % 101 - 50;
		(*pCoords)[i][2] = rand() % 101 - 50;
		cout << "Particle " << i << ": \t" << (*pCoords)[i][0] << "\t" << (*pCoords)[i][1] << "\t" << (*pCoords)[i][2] << "\t" << endl;
	}
}

System::~System() { cout << "Destructor call." << endl; }

int System::GetCoordinate ( int partNumber, int axis) {
	return (*pCoords)[partNumber][axis];
}



int main()
{
	srand(time(NULL));
	int number;
	cout << "Number of Particles: ";
	cin >> number;

	//struct timeval start, end;
	//gettimeofday(&end,NULL);

	System MC(number);

	//gettimeofday(&end,NULL);
	//cout << "Time needed to create System: " << (float) ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec) / 1000000.0 << endl;

	cout << "How many of the Coordinates would you like to see again? ";
	cin >> number;
	for ( int i = 0; i < number; i++ ){
		cout << "X: " << MC.GetCoordinate(i, 0) << "\t Y: " << MC.GetCoordinate(i, 1) << "\t Z: " << MC.GetCoordinate(i, 2) << endl;
	}

	

	


	/*int *pVectors = new int[3*n];
	int *pI = pVectors;
	int sum=0;

	for (i = 0; i < 3*n; pI++, i++ ){
		*pI = rand() % 101 - 50;
	}

	pI = pVectors;

	for (i = 0; i < 3*n; i++, pI++){
		sum = sum + *pI;
	}

	cout << "Sum: " << sum << endl;

	int vectors[n][3], sum[3] = {0,0,0};
	for (i=0; i < n; i++){
		for (j=0; j<3; j++){
			vectors[i][j]=rand() % 101 - 50;
		}
	}
	for (i=0; i < 3; i++){
		for (j=0; j<n; j++){
			sum[i] = sum[i] + vectors[j][i];
		}
	}
	cout << "SumX: " << sum[0] << "  SumY: " << sum[1] << "  SumZ: " << sum[2] << endl;
	float result = sum[0]+sum[1]+sum[2];
	cout << "Sum: " << result << endl;*/


    
	return 0;
}
/*
double Energy( int coords[] ) {
	double energy = 0;
	int dist[n*(n-1)];
	return energy;
}*/
