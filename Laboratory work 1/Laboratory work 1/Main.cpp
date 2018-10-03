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

	List<Circle> *list = new ListOnLibraryFunction<Circle>;
	
	checker(*list, criterion);

	return 0;
}