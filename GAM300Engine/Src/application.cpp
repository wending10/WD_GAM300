
#include <vector>

#include "application.h"

namespace TDS
{
     Application::Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname)
        :m_window(hinstance, nCmdShow, classname)
     {
         m_window.createWindow();
         m_pVKInst = std::make_shared<VulkanInstance>(m_window);
	 }

     void Application::Initalize()
     {
         
     }
     void Application::Update()
     {
         while (m_isRunning)
         {
             m_isRunning = m_window.processInputEvent();
         }
     }
     Application::~Application()
     {
         m_window.~WindowsWin();
        
     }

}// end TDS