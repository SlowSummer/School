#include <string>

using namespace std;
class DOg
{
private:
	string name;
	int age;
public:
	void setName(string);
	void setAge(int);
	void swapDog(DOg);
	void swapAge(DOg&);

	string getName();
	int getAge();
};

