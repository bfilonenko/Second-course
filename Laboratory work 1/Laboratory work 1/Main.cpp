#include <list>
#include "Checker.h"


template<typename T>
bool criterion(T value)
{
	return value < 0;
}


int main()
{
	List<int> *list = new CyclicListOnDynamicArray<int>;
	
	checker(*list, criterion);

	return 0;
}