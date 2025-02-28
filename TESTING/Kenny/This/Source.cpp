#include <iomanip>
#include "DOg.h"
#include <iostream>
using namespace std;

int main()
{
	
	DOg dog1;
	DOg dog2;

	dog1.setName("Leema");
	dog2.setName("Anna Bark");
	dog1.setAge(3);
	dog2.setAge(1000);

	cout << dog1.getName() << endl;
	cout << dog2.getName() << endl;
	cout << dog1.getAge() << endl;
	cout << dog2.getAge() << endl;

	cout << endl << endl;
	dog1.swapDog(dog2);

	cout << dog1.getName() << endl;
	cout << dog2.getName() << endl;
	cout << dog1.getAge() << endl;
	cout << dog2.getAge() << endl;



	return 0;
}