#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

class System {
	private:	
		int coords[][3];
		int n;
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

};

System::System( int numberOfParticles ) {
	n = numberOfParticles;
	int i = 0;
	cout << "These are the " << n << " Particles:" << endl;
	while (i < n) {
		coords[i][0] = rand() % 101 - 50;
		coords[i][1] = rand() % 101 - 50;
		coords[i][2] = rand() % 101 - 50;
		cout << "Particle " << i << ": \t" << coords[i][0] << "\t" << coords[i][1] << "\t" << coords[i][2] << "\t" << endl;
		cout << "Particle " << i << " created, continuing with Particle " << i + 1 << endl;
		i++;
	}
}

System::~System() { cout << "Destructor call." << endl; }

int System::GetCoordinate ( int partNumber, int axis ) {
	return coords[partNumber][axis];
}



int main()
{
	srand(time(NULL));
	int number;
	cout << "Number of Particles: ";
	cin >> number;

	struct timeval start, end;
	gettimeofday(&start,NULL);

	System MC(number);

	gettimeofday(&end,NULL);
	cout << "Time needed to create System: " << (float) ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec) / 1000000.0 << endl;

	cout << "The Coordinates of which Particle do you want to know? ";
	cin >> number;
	cout << "X: " << MC.GetCoordinate(number, 0) << "\t Y: " << MC.GetCoordinate(number, 1) << "\t Z: " << MC.GetCoordinate(number, 2) << endl;

	

	


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
