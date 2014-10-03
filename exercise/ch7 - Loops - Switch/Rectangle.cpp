# include <iostream>
# include "Rectangle.hpp"
using namespace std;

Rectangle::Rectangle( int width, int height ) {
	itsWidth = width;
	itsHeight = height;
}

Rectangle::~Rectangle() {}

enum CHOICE {
	drawRect = 1,
	getArea,
	getPerim,
	changeDimensions,
	quit
};

int doMenu();
void doDrawRect( Rectangle );
void doGetArea( Rectangle );
void doGetPerim( Rectangle );

int main()
{
	Rectangle theRect( 30, 5 );

	int choice = drawRect;

	int fQuit = false;

	while ( !fQuit ) {
		choice = doMenu();

		if ( choice < drawRect || choice > quit ) {
			cout << "\nInvalid choice, try again.\n\n";
			continue;
		}

		switch ( choice ) {
			case drawRect:
				doDrawRect( theRect );
				break;
			case getArea:
				doGetArea( theRect );
				break;
			case getPerim:
				doGetPerim( theRect );
				break;
			case changeDimensions:
				int newHeight, newWidth;
				cout << "\nNew width: ";
				cin >> newWidth;
				cout << "\nNew height: ";
				cin >> newHeight;
				theRect.setSize( newWidth, newHeight );
				doDrawRect( theRect );
				break;
			case quit:
				fQuit = true;
				cout << "\nExiting... \n\n";
				break;
			default:
				cout << "Error in choice!\n";
				fQuit = true;
				break;
		}
	}
	
	return 0;
}

int doMenu() {
	int choice;

	cout << endl << endl;
	cout << "   *** Menu ***   " << endl;
	cout << "(1) Draw Rectangle" << endl;
	cout << "(2) Area" << endl;
	cout << "(3) Perimeter" << endl;
	cout << "(4) Resize" << endl;
	cout << "(5) Quit" << endl;

	cin >> choice;
	return choice;
}

void doDrawRect( Rectangle rect ) {
	int height = rect.getHeight();
	int width = rect.getWidth();

	for ( int i=0; i < height; i++ ) {
		for ( int j=0; j < width; j++ )
		 cout << "* ";
		cout << endl;	
	}
}

void doGetArea( Rectangle rect ) {
	cout << "Area: " << rect.getArea() << endl;
}

void doGetPerim( Rectangle rect ) {
	cout << "Perimter: " << rect.getPerim() << endl;
}
