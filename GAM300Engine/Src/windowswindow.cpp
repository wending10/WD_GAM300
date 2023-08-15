#include "windowswindow.h"

WindowsWin::WindowsWin(){}

WindowsWin::~WindowsWin() 
{
	if (m_handleWindows != nullptr)
	{
		DestroyWindow(m_handleWindows);
	}
}

bool WindowsWin::registerWins()
{
	WNDCLASSEX wc; //windows class
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	
	return false;

}