typedef unsigned short int USHORT;

class Employee
{
	private:
		USHORT itsAge;
		USHORT itsYearsOfService;
		float itsSalary;

	public:
		Employee( USHORT age, USHORT yearsOfService, float salary );
		~Employee();

		USHORT getTotalIncome(); 
		
		// Getter and Setter
		USHORT getAge() const { return itsAge; };
		USHORT getYearsOfService() const { return itsYearsOfService; };
		float getSalary() const { return itsSalary; };
		void setAge( USHORT age ) { itsAge = age; };
		void setYearsOfService( USHORT yearsOfService ) { 
			itsYearsOfService = yearsOfService; };
		void setSalary( float salary ) { itsSalary = salary; };
};
