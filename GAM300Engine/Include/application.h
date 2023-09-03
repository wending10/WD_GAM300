#ifndef APPLICATION
#define APPLICATION

#include <iostream>

#include "windowswindow.h"
#include "vulkanTools/vulkanInstance.h"


namespace TDS
{
	class Application
	{
	public:
	
	    Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname, WNDPROC wndproc);
		~Application();
		
		void   Initialize();
		void   Update();
		void   Render() {}
		void   Exit() {}

		void handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		Application(const Application&);
		Application& operator=(const Application&) {}

	private:
		WindowsWin						 m_window;
		bool							 m_isRunning{ true };
		std::shared_ptr <VulkanInstance> m_pVKInst;

	};//class application





}//namespace TDS


#endif // !APPLICATION

