#include <iostream>

// Function Demonstration Function
// prints out a useful message
void DemonstrationFunction()
{
	std::cout << "In Demonstration Function" << std::endl;
}

int main()
{
	std::cout << "In main" << std::endl;
	DemonstrationFunction();
	std::cout << "Back in main" << std::endl;
	return 0;
}
