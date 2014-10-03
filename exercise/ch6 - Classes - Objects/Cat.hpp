# include <iostream>

using namespace std;

class Cat
{
	private:	
		unsigned int mAge;
		float mWeight;

	public:
		// Con- and Destructor
		Cat( unsigned int iniAge, float iniWeight );
		~Cat();
		// Methods
		void makeNoise();
		// Getter
		unsigned int getAge() const { return mAge; };
		float getWeight() const { return mWeight; };
		// Setter
		void setAge( unsigned int age ) { mAge = age; };
		void setWeight( float weight ) { mWeight = weight; };
};
