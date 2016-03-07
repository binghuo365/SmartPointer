#include <iostream>
#include "refShared.h"
#include <vector>
#include "handle.h"
class object
	: public CRefShared
{
public:
	object() : i(0)
	{
		std::cout << "construct" << std::endl;
	}
	~object()
	{
		std::cout << "deconstruct" << std::endl;
	}

	void printHelloWorld()
	{
		std::cout << "hello world" << std::endl;
	}

public:
	int i;
};

typedef CHandle<object> objectPtr;

int main()
{
	objectPtr obj = new object();
	obj->i = 1;
	objectPtr obj2 = obj;
	obj->printHelloWorld();
	objectPtr obj3 = new object();
	obj3->i = 3;
	std::vector<objectPtr> vecObj;
	object ob;
	ob.printHelloWorld();
	vecObj.push_back(obj);
	vecObj.push_back(obj3);

	obj = obj3;
	std::cout << obj->i << std::endl;

	*obj = *obj3;
	std::cout << obj->i << std::endl;

	system("pause");
	return 0;
}