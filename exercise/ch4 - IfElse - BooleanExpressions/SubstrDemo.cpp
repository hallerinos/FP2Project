# include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	unsigned int difference;
	unsigned int bigNumber = 100;
	unsigned int smallNumber = 50;

	difference = bigNumber - smallNumber;
	cout << "Difference is " << difference << endl;

	difference = smallNumber - bigNumber;
	cout << "Difference is " << difference << endl;
	return 0;
}
