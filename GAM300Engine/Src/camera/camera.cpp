#include "camera/camera.h"

namespace TDS
{
	TDSCamera::TDSCamera(float Yaw, float pitch, Vec3 position, Vec3 up)
	{

		m_Position = position;
		m_WorldUp = up;
		m_Yaw = Yaw;
		m_Pitch = pitch;
		updateViewMatrix();
	}

	
	Mat4 TDSCamera::GetViewMatrix() const
	{
		return Mat4::LookAt(m_Position, m_Position + m_Front, m_Up);
	}


	void TDSCamera::updateViewMatrix()
	{
		// calculate the new Front vector
		Vec3 front;
		front.x = Mathf::Cos(m_Yaw * Mathf::Deg2Rad) * Mathf::Cos(m_Pitch * Mathf::Deg2Rad);
		front.y = Mathf::Sin(m_Pitch * Mathf::Deg2Rad);
		front.z = Mathf::Sin(m_Yaw * Mathf::Deg2Rad) * Mathf::Cos(m_Pitch * Mathf::Deg2Rad);
		m_Front = Vec3::Normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = Vec3::Normalize(Vec3::Cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = Vec3::Normalize(Vec3::Cross(m_Right, m_Front));

		m_Down = -m_Up;
	}

	void TDSCamera::UpdateCamera(float deltaTime)
	{
		if (moving())
		{
			float CameraSpeed = m_Speed * deltaTime;
			if (keys.up)
			{
				m_Position += m_Front * CameraSpeed;

			}
			if(keys.down)
				m_Position -= m_Front * CameraSpeed;
			if(keys.left)
				m_Position -= m_Right * CameraSpeed;
			if(keys.right)
				m_Position += m_Right * CameraSpeed;
		}
		updateViewMatrix();
	}


	bool TDSCamera::moving()
	{
		if (Input::keystatus == Input::KeyStatus::PRESSED || Input::keystatus == Input::KeyStatus::REPEATED)
		{
			switch (Input::keyCode)
			{
				case TDS_W:
					return keys.up = true;
					break;

				case TDS_A:
					return keys.left = true;
					break;

				case TDS_S:
					return keys.down = true;
					break;

				case TDS_D:
					return keys.right = true;

				default:
					return false;
			}
		}
		else
		{
			keys.up		= false;		  
			keys.left	= false;				  
			keys.down	= false;			  
			keys.right	= false;
		}
		return false;
	}
}