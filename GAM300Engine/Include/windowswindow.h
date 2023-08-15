#ifndef WINDOWS_WINDOW
#define WINDOWS_WINDOW


#include <Windows.h>
#include <tuple>
class WindowsWin
{
public:
	 WindowsWin();
	~WindowsWin();


	bool					registerWins();
	bool					createWindow()		noexcept;

	int						getWidth()			const	{ return m_Width; }
	int						getHeight()			const	{ return m_Height;}
	std::tuple<int, int>	getPosition()		const
	{
		POINT points{ 0, 0 };
		ClientToScreen(m_handleWindows, &points);
		return {static_cast<int>(points.x), static_cast<int>(points.y) };
	}

	std::size_t				getWindowsHandle()  const
	{
		return reinterpret_cast <std::size_t> (m_handleWindows);
	}

private:

	HWND m_handleWindows{ nullptr };

	int	 m_Width{};
	int	 m_Height{};


};




#endif // !WINDOWS_WINDOW
