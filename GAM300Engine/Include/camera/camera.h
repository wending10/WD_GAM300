#ifndef TDS_CAMERA
#define TDS_CAMERA

#include "TDSMath.h"
#include "Input.h"

namespace TDS
{
	class TDSCamera
	{
	public:

		TDSCamera(float Yaw, float pitch, Vec3 position = { 0.0f, 0.0f, 2.0f }, Vec3 up = { 0.0f, 1.0f, 0.0f });

		//using lookat and Euler Angles
		Mat4 GetViewMatrix() const;

	private:
		
		//camera attributes
		Vec3	m_Position{};
		Vec3	m_Front{};
		Vec3	m_Up{0.f,0.f,1.f};
		Vec3	m_Right{};
		Vec3	m_Down{};
		Vec3	m_WorldUp{};

		//euler angles
		float	m_Yaw{};
		float	m_Pitch{};

		//option to toggle with
		float	m_Speed{};
		float	m_mouseSensitivity{}; //should it be in input???
		float	m_ZoomLevel{};
		float	m_Width{};
		float	m_Height{};

		void updateViewMatrix();
	};




}//namespace TDS


#endif // !TDS_CAMERA
