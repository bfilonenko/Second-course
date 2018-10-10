#include "WindowController.h"


void demonstration()
{
	vector<WorkWithWindow> windows;
	
	ifstream fileIn("Data/Data for window controller.dat");
	string mainWindowName;
	getline(fileIn, mainWindowName);

	int numberOfAlgorithm;
	fileIn >> numberOfAlgorithm;

	string *windowName = new string[numberOfAlgorithm];
	if (numberOfAlgorithm != 0)
	{
		getline(fileIn, windowName[0]);
		for (int i = 0; i < numberOfAlgorithm; ++i)
		{
			getline(fileIn, windowName[i]);
		}
	}
	fileIn.close();

	WorkWithWindow mainWindow(mainWindowName);
	windows.push_back(mainWindow);

	while (windows.size() != 0)
	{
		for (int i = 0; i < windows.size(); ++i)
		{
			windows[i].work();
		}

		windows.erase(remove_if(windows.begin(), windows.end(), [](WorkWithWindow window) { return !window.isOpen(); }), windows.end());
	}
}