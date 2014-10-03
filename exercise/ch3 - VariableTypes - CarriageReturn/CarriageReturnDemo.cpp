# include <iostream>

int main()
{
	int length = 1234567;
	for ( int i = 1; i < length + 1; i++ )
		std::cout << "\rCarriage return demo:" << (float) i/length*100;
	std::cout << "\nFinished." << std::endl;
	return 0;
}
