#include <list>
#include "Checker.h"
#include "CheckerForFigure.h"


template<typename T>
bool criterion(T value)
{
	return true;
}


int main()
{
	checkerForFigure();

	List<Line> *list = new ListOnLinkedList<Line>;
	
	checker(*list, criterion);

	return 0;
}