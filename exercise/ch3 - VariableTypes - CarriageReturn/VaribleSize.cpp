# include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	cout << "The size of an int is: \t\t" << sizeof( int ) 
		<< " bytes." <<endl;
	cout << "The size of an short is: \t" << sizeof( short ) 
		<< " bytes." <<endl;
	cout << "The size of an long is: \t" << sizeof( long ) 
		<< " bytes." <<endl;
	cout << "The size of an char is: \t" << sizeof( char ) 
		<< " bytes." <<endl;
	cout << "The size of an float is: \t" << sizeof( float ) 
		<< " bytes." <<endl;
	cout << "The size of an double is: \t" << sizeof( double ) 
		<< " bytes." <<endl;
	cout << "The size of an bool is: \t" << sizeof( bool ) 
		<< " bytes." <<endl;
	return 0;
}
