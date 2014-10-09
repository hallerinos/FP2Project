# include <iostream>

using namespace std;

class SimpleCat
{
	public:
		SimpleCat();
		~SimpleCat();
		void setAge( int newAge ) { 
			itsAge = newAge; 
		};
		int getAge() { 
			return itsAge;
	 };
		int *getAdress() {
			return &itsAge;
		};
	private:
		int itsAge;
};

SimpleCat::SimpleCat() {
	setAge( 1 );
}

SimpleCat::~SimpleCat() {
	cout << "Destructor called." << endl;
}

int main()
{
	SimpleCat *Frisky = new SimpleCat;
	int *privateAdress = Frisky->getAdress();
	cout << "Friskys age: " << Frisky->getAge() << endl;
	*privateAdress = 10;
	cout << "Friskys age: " << Frisky->getAge() << endl;

	return 0;
}
