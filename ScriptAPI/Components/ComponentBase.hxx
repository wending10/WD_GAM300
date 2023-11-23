#pragma once

#include "../IncludeFromEngine.hxx"
#include "../Vector3.hxx"
#include "../Vector4.hxx"

namespace ScriptAPI
{
	private interface class ComponentBase
	{
		virtual void SetEntityID(TDS::EntityID ID) = 0;
	};
}