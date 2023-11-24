#include "GameObject.hxx"

namespace ScriptAPI
{
	BoxColliderComponent GameObject::GetBoxColliderComponent()
	{
		return BoxColliderComponent(entityID);
	}
	CameraComponent GameObject::GetCameraComponent()
	{
		return CameraComponent(entityID);
	}
	CapsuleColliderComponent GameObject::GetCapsuleColliderComponent()
	{
		return CapsuleColliderComponent(entityID);
	}
	NameTagComponent GameObject::GetNameTagComponent()
	{
		return NameTagComponent(entityID);
	}
	RigidBodyComponent GameObject::GetRigidBodyComponent()
	{
		return RigidBodyComponent(entityID);
	}
	SphereColliderComponent GameObject::GetSphereColliderComponent()
	{
		return SphereColliderComponent(entityID);
	}

	TransformComponent GameObject::GetTransformComponent()
	{
		return TransformComponent(entityID);
	}

	UISpriteComponent GameObject::GetUISpriteComponent()
	{
		return UISpriteComponent(entityID);
	}

	int GameObject::GetEntityID()
	{
		return entityID;
	}

	generic <typename T>
	T GameObject::GetComponent()
	{
		System::Type^ type = T::typeid;

		if (type == BoxColliderComponent::typeid)
		{
			return safe_cast<T>(BoxColliderComponent());
		}
		else if (type == CameraComponent::typeid)
		{
			return safe_cast<T>(CameraComponent());
		}
		else if (type == CapsuleColliderComponent::typeid)
		{
			return safe_cast<T>(CapsuleColliderComponent());
		}
		else if (type == NameTagComponent::typeid)
		{
			return safe_cast<T>(NameTagComponent());
		}
		else if (type == RigidBodyComponent::typeid)
		{
			return safe_cast<T>(GetRigidBodyComponent());
		}
		else if (type == SphereColliderComponent::typeid)
		{
			return safe_cast<T>(GetSphereColliderComponent());
		}
		else if (type == TransformComponent::typeid)
		{
			return safe_cast<T>(GetTransformComponent());
		}
		else if (type == UISpriteComponent::typeid)
		{
			return safe_cast<T>(GetUISpriteComponent());
		}

		return T();
	}

	void GameObject::SetEntityID(TDS::EntityID id)
	{
		entityID = id;
		transform = TransformComponent(id);
	}
}