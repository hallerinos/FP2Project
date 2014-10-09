# include <iostream>

int main()
{
	int x = 0;
	int a = x++;
	std::cout << "a: " << a << " x: " << x;
	int b = ++x;
	std::cout << " b: " << b << " x: " << x;
	return 0;
}
