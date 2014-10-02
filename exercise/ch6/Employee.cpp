# include <iostream>
# include "Employee.hpp"

typedef unsigned short int USHORT;

Employee::Employee( USHORT age, USHORT yearsOfService, float salary ) {
	itsAge = age;
	itsYearsOfService = yearsOfService;
	itsSalary = salary;
}
Employee::~Employee() {}

USHORT Employee::getTotalIncome() {
	float salary = Employee::getSalary();
	float incomePerYear = salary * 12 / 1000;
	USHORT incomePYShort = (USHORT) incomePerYear;	// Cut the thousands
	if ( incomePerYear - incomePYShort >= 0.5 )	// Test which int is nearest
		return ( (incomePYShort + 1) * 1000 );
	else
		return ( incomePYShort * 1000 );
}

int main() 
{
	Employee empOne( 27, 5, 4253.37 );
	Employee empTwo( 57, 25, 5321.92 );

	std::cout << "Our company runs with two employees, the younger one is " 
		<< empOne.getYearsOfService() 
		<< " years in service and earns exactly "
		<< empOne.getSalary() * 12 
		<< " Dollars per year. Employee two is " 
		<< empTwo.getYearsOfService() << " years in service and earns "
		<< empTwo.getSalary() * 12 << " Dollars per year.\n\n"
		<< "Their total income per year is rounded to the nearest 1000:\n"
		<< empOne.getTotalIncome() << " and " << empTwo.getTotalIncome() 
		<< " Dollars per Year.\n\n"
		<< "Employee one has been promised a raise by 1000 Dollars now.\n";
	
	empOne.setSalary( empOne.getSalary() + 1000 );
	empOne.setYearsOfService( empOne.getYearsOfService() + 1 );

	std::cout << "In his " 
		<< empOne.getYearsOfService() << "'th year of service, he earns: " 
		<< empOne.getSalary() << " Dollars a month and "
		<< empOne.getTotalIncome() << " per year.\n\n";
	return 0;
}
