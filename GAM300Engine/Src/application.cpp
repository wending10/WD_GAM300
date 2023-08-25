#include"application.h"

namespace TDS
{
	 Application::Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname)
		 :m_window(hinstance, nCmdShow, classname)
	 { 
	 }

     void Application::Initialize()
     {
         m_window.createWindow();
     }
     void Application::Update()
     {
         while (m_isRunning)
         {
             m_isRunning = m_window.processInputEvent();
         }
     }

}// end TDS