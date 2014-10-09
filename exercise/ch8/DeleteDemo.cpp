# include <iostream>

using namespace std;

class SimpleCat
{
	public:
		SimpleCat();
		~SimpleCat();
		void setAge( int newAge ) { 
			cout << "setAge called" << endl;
			cout << "Adress of itsAge: " << &itsAge << endl;
			itsAge = newAge; };
		int getAge() { 
			cout << "getAge called, adress of itsAge: " << &itsAge;
			return itsAge; };
	private:
		int itsAge;
};

SimpleCat::SimpleCat() {
	cout << "Constructor called." << endl;
	setAge( 1 );
}

SimpleCat::~SimpleCat() {
	cout << "Destructor called." << endl;
}

int main()
{
	cout << "SimpleCat Frisky..." << endl;
	SimpleCat Frisky;
	cout << "SimpleCat *pRags = new SimpleCat..." << endl;
	SimpleCat * pRags = new SimpleCat;
	cout << "delete pRags... " << endl;
	delete pRags;
	cout << "Exiting, watch Frisky go..." << endl;

	return 0;
}
