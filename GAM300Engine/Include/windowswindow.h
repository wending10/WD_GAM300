#ifndef WINDOWS_WINDOW
#define WINDOWS_WINDOW

//reduce code from windows.h 
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <Windows.h>
#include <string>

namespace TDS
{
	class WindowsWin
	{
	public:		//functions
				WindowsWin(HINSTANCE hInstance, int nCmdShow, const wchar_t* className);
				~WindowsWin();

     int		getWidth()  const noexcept;
	 int		getHeight() const noexcept;

	 bool		registerWindow();
	 bool		createWindow();
	 bool		processInputEvent();

	 static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	private:	//functions

	public:		//variables


	private:	//variables

		HWND	  m_handleWindows {};
		HINSTANCE m_hInstance	  {};
		int		  m_Width		  {};
		int		  m_Height		  {};
		int		  m_cmdshow		  {};

		std::wstring_view  m_classname	{};


		static constexpr int minWidth {1240};
		static constexpr int minHeight {800};
	};

}//end TDS


#endif // !WINDOWS_WINDOW
