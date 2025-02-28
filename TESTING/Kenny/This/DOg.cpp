#include "DOg.h"



void DOg::setName(string newName)
{
	name = newName;
}

void DOg::setAge(int newAge)
{
	this->age = newAge;
}



void DOg::swapDog(DOg otherDog)
{
	string temp;
	temp = this->name;

	this->name = otherDog.name;
	otherDog.name = temp;
	otherDog.swapAge(*this);
}

void DOg::swapAge(DOg& otherDog)
{
	int temp = this->age;
	this->age = otherDog.age;
	otherDog.age = temp;
}

string DOg::getName()
{
	return name;
}
int DOg::getAge()
{
	return this->age;
}
;
