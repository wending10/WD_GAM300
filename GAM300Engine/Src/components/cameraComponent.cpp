/*!*************************************************************************
****
\file cameraComponent.cpp
\author Go Ruo Yan, Matthew Cheung
\par DP email: ruoyan.go@digipen.edu, j.cheung@digipen.edu
\date 28-9-2023
\brief  This program defines functions of cameraComponent class
****************************************************************************
***/

#include "components/cameraComponent.h"

RTTR_REGISTRATION
{
	using namespace TDS;

rttr::registration::class_<CameraComponent>("Camera Component")
	.property("Yaw", &CameraComponent::getYaw, &CameraComponent::setYaw)
	.property("Pitch", &CameraComponent::getPitch, &CameraComponent::setPitch)
	.property("Position", &CameraComponent::getPosition, rttr::select_overload<void(Vec3)>(&CameraComponent::setPosition))
	.property("Speed", &CameraComponent::getSpeed, &CameraComponent::setSpeed)
	.property("FOV", &CameraComponent::getFOV, &CameraComponent::setFOV)
	.property("MouseSensitivity", &CameraComponent::getMouseSensitivity, &CameraComponent::setMouseSensitivity);
}

namespace TDS 
{
	/*!*************************************************************************
	Initializes the CameraComponent when created
	****************************************************************************/
	CameraComponent::CameraComponent(): m_Position(Vec3 (0.f, 0.f, 0.f)),
										m_Yaw(-90.f),
										m_Pitch(0.f),
										m_Speed(1.0f),
										m_Fov(45.f),
										m_mouseSensitivity(0.1f)
										
	{ }

	//Mat4 CameraComponent::GetViewMatrix() const
	//{
	//	return Mat4::LookAt(m_Position, m_Position + m_Front, m_Up);
	//}

	/*!*************************************************************************
	Initializes the CameraComponent when created, given another CameraComponent
	to move (for ECS)
	****************************************************************************/
	CameraComponent::CameraComponent(CameraComponent&& toMove) noexcept : m_Position(toMove.m_Position),
																		 m_Yaw(toMove.m_Yaw),
																		 m_Pitch(toMove.m_Pitch),
																		 m_Speed(toMove.m_Speed),
																		 m_Fov(toMove.m_Fov),
																		 m_mouseSensitivity(toMove.m_mouseSensitivity)
	{ }

	CameraComponent* GetCameraComponent(EntityID entityID)
	{
		return ecs.getComponent<CameraComponent>(entityID);
	}

}