/*
 * Listing of std::cout and test for any compiler bugs
 * */
#include <iostream>

int main()
{
	std::cout << "Is it buggy or not...?" << std::endl; 
	std::cout << 8+5 << std::endl;
	std::cout << (8+5) << std::endl;
	std::cout << "Nope.";
	return 0;
}
