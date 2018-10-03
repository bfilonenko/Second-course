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

	List<vector<int> > *list = new ListOnLinkedList<vector<int> >;
	
	checker(*list, criterion);

	return 0;
}