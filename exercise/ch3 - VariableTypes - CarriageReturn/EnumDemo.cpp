# include <iostream>

int main()
{
	enum COLOR 
	{
		RED		= 0, 
		GREEN = 1, 
		BLUE 	= 2
	};
	
	for ( int i = 0; i < 3; i++  )
		if ( i == RED )
			std::cout << "yay, " << i << " is red." << std::endl;
		else
			std::cout << i << " is not red." << std::endl;
	return 0;
}
