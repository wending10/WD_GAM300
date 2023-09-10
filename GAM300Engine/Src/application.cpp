
#include <vector>

#include "application.h"
#include "Input.h"
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
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        {
            Input::processMouseInput(wParam, lParam);
        }break;

        case WM_MOUSEMOVE:
        {
            Input::updateMousePosition(lParam);
        }break;

        case WM_MOUSEWHEEL:
        {
            Input::processMouseScroll(wParam);
        }break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            uint32_t VKcode = wParam;
            bool wasDown = (lParam & (1 << 30)) != 0;
            bool isDown = (lParam & (1 << 31)) == 0;
            Input::processKeyboardInput(VKcode, wasDown, isDown);
        }break;
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
             if (Input::isMouseScrollDown())
                 std::cout << "scrolling mouse up\n";




             Input::scrollStop();
         }
         vkDeviceWaitIdle(m_pVKInst.get()->getVkLogicalDevice());
     }
     Application::~Application()
     {
         m_window.~WindowsWin();
        
     }

}// end TDS