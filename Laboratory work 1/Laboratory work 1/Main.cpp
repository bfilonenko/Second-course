#include <list>
#include "Checker.h"
#include "CheckerForFigure.h"


template<typename T>
bool criterion(T value)
{
	return value < 0;
}


int main()
{
	checkerForFigure();

	List<int> *list = new ListOnLinkedList<int>;
	
	checker(*list, criterion);

	return 0;
}