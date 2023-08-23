#ifndef APPLICATION
#define APPLICATION

#include <iostream>

#include "windowswindow.h"

namespace TDS
{
	class Application
	{
	public:
	
	    Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname);
		~Application() {}
		
		void   Initalize();
		void   Update();
		void   Render(float aspectRatio) {}
		void   Exit() {}



	private:
		Application(const Application&);
		Application& operator=(const Application&) {}

	private:
		WindowsWin m_window;
		bool	   m_isRunning{ true };

	};//class application





}//namespace TDS


#endif // !APPLICATION

