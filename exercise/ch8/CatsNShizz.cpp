# include <iostream>

using namespace std;

class SimpleCat 
{
	public:
		SimpleCat();
		~SimpleCat();
		void setAge( int newAge ) { 
			(*this).itsAge = newAge; 
		};
		int getAge() const { 
			return itsAge;
	 };
	private:
		int itsAge;
};

SimpleCat::SimpleCat() {
	setAge( 1 );
}

SimpleCat::~SimpleCat() {
}

int main()
{
	int num = 10;
	int &rNum = num;
	num = 9;

	cout << "num: " << num
		<< " rNum: " << rNum
		<< " &num: " << &num
		<< " &rNum: " << &rNum;
	return 0;
}
