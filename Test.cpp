#include <iostream>
#include "refShared.h"
#include <vector>
#include "handle.h"
class object
	: public CRefShared
{
public:
	object(){}
	~object(){}

	void printHelloWorld()
	{
		std::cout << "hello world" << std::endl;
	}

private:

};

typedef CHandle<object> objectPtr;

int main()
{
	objectPtr obj = new object();
	objectPtr obj2 = obj;
	obj->printHelloWorld();
	objectPtr obj3 = new object();
	std::vector<objectPtr> vecObj;
	object ob;
	ob.printHelloWorld();
	vecObj.push_back(obj);
	vecObj.push_back(obj3);
	return 0;
}