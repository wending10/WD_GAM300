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

		void UpdateCamera(float deltaTime);

		bool moving();

	private:
		
		struct {
			bool left	{ false };
			bool right	{ false };
			bool up		{ false };
			bool down	{ false };
		}keys;
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
		float	m_Speed{1.0f};
		float	m_mouseSensitivity{}; //should it be in input???
		float	m_ZoomLevel{};
		float	m_Width{};
		float	m_Height{};

		void updateViewMatrix();
		void translate(Vec3 deltaWheel); // act like zoom?

	};




}//namespace TDS


#endif // !TDS_CAMERA
