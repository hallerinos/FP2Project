/*
 * Listing of std::cout and test for any compiler bugs
 * */
#include <iostream>

int main()
{
//	std::cout << "Is it buggy or not...?" << std::endl; 
//	std::cout << 8+5 << std::endl;
//	std::cout << (8+5) << std::endl;
//	std::cout << "Nope.";
//	return 0;

//  Way #1 for dismissing std::
//	using std::cout;
//	using std::endl;

//  Way #2 for dismissing std::
	using namespace std;
	cout << "Is it buggy or not...?\t\t" << std::endl;
	cout << "\t\t\t " << 8+5 << endl;
	cout << "\t\t\t " << (8+5) << endl;
	cout << "\t\t\t ...nope.";
}
