# include <iostream>
# include "Cat.hpp"

using namespace std;

Cat::Cat( unsigned int iniAge, float iniWeight ) {
	cout << "Constructor call." << endl;
	mAge = iniAge;
	mWeight = iniWeight;
}
Cat::~Cat() { cout << "Destructor call." << endl; }

void Cat::makeNoise() {
	cout << "Purr!";
}

int main()
{
	Cat susi( 12, 3.5 );
	cout << "Susi is a cat, " 			<< susi.getAge() 
		<< " years old and weights " 	<< susi.getWeight() << "kg." << endl
		<< "She is able to purr. Susi: '";
	susi.makeNoise();
	cout << "'."<< endl;
	return 0;
}
