class Rectangle 
{
	private:
		int itsHeight;
		int itsWidth;
	
	public:
		Rectangle( int width, int height );
		~Rectangle();
		int getArea() const { return ( itsHeight * itsWidth ); };
		int getPerim() const { return ( 2 * ( itsHeight + itsWidth ) ); };
	
		// getter and setter
		int getHeight() const { return itsHeight; };
		int getWidth() const { return itsWidth; };
		void setSize( int width, int height ) {
			itsWidth = width;
			itsHeight = height;
		};
};

