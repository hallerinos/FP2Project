# include <iostream>

int main()
{
	int x = 0;
	int a = ++x;
	std::cout << "a: " << a << " x: " << x;
	x = 0;
	int b = x++;
	std::cout << " b: " << b << " x: " << x;
	return 0;
}
