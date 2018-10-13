#include "WindowController.h"


void demonstration()
{
	vector<WorkWithWindow> windows;
	
	ifstream fileIn("Data/Data for window controller.dat");
	string mainWindowName;
	getline(fileIn, mainWindowName);

	fileIn.close();

	WorkWithWindow mainWindow(mainWindowName);
	windows.push_back(mainWindow);

	while (windows.size() != 0)
	{
		size_t length = windows.size();
		for (int i = 0; i < length; ++i)
		{
			windows[i].work();
			
			for (int j = 0; j < windows[i].getNewWindowName().size(); ++j)
			{
				WorkWithWindow window(windows[i].getNewWindowName()[j]);
				windows.push_back(window);
			}
			windows[i].cleanNewWindowName();
		}

		windows.erase(remove_if(windows.begin(), windows.end(), [](WorkWithWindow window) { return !window.isOpen(); }), windows.end());
	}
}
