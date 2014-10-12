#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>



using namespace std;

double Energy( int coords[] );

const int n = 500;
int main()
{
	srand(time(NULL));

	int i;

	struct timeval start, end;
	gettimeofday(&start,NULL);

	int *pVectors = new int[3*n];
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

/*	int vectors[n][3], sum[3] = {0,0,0};
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


    gettimeofday(&end,NULL);
    cout << (float) ((end.tv_sec - start.tv_sec)*1000000 + end.tv_usec - start.tv_usec) / 1000000.0 << endl;
	return 0;
}

double Energy( int coords[] ) {
	double energy = 0;
	int dist[n*(n-1)];
	return energy;
}
