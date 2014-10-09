# include <iostream>

int main()
{
	for ( unsigned char i = 32; i < 128; i++ )
		std::cout << (char) i;
	return 0;
}
