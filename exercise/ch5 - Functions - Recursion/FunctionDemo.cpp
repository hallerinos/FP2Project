# include <iostream>
# include "area.hpp"

using namespace std;

int area( int length, int width = 1);

int main()
{
	int lengthOfYard;
	int widthOfYard;
	int areaOfYard;

	cout << "\nHow wide is your yard? ";
	cin >> widthOfYard;
	cout << "\nHow long is your yard? ";
	cin >> lengthOfYard;

	areaOfYard = area( lengthOfYard, widthOfYard );

	cout << "\nYour yard is ";
	cout << areaOfYard;
	cout << " square meters." << endl << endl;

	return 0;
}
