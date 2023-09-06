
#include <vector>

#include "application.h"

namespace TDS
{
     Application::Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname, WNDPROC wndproc)
        :m_window(hinstance, nCmdShow, classname)
     {
         m_window.createWindow(wndproc);
         m_pVKInst = std::make_shared<VulkanInstance>(m_window);
	 }
     void  Application::handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
     {
         //ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam); for imgui implementation
         //can extern  some imgui wndproc handler | tbc

        switch (uMsg)
        {

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            ValidateRect(m_window.getWindowHandler(), NULL);
            break;
        case WM_SIZE: //for resize of window may need it for fullscreen?
            m_window.setWidth(LOWORD(lParam));
            m_window.setHeight(HIWORD(lParam));
            break;

        }
     }
     void Application::Initialize()
     {
         
     }
     void Application::Update()
     {
         while (m_isRunning)
         {
             m_pVKInst.get()->drawFrame(m_window);
             m_isRunning = m_window.processInputEvent(); //process event after rendering????
         }
         vkDeviceWaitIdle(m_pVKInst.get()->getVkLogicalDevice());
     }
     Application::~Application()
     {
         m_window.~WindowsWin();
        
     }

}// end TDS