#include "camera/camera.h"

namespace TDS
{
	TDSCamera::TDSCamera(float Yaw, float pitch, Vec3 position, Vec3 up)
	{

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

}