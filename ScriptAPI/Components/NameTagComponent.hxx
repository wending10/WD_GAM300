#pragma once

#include "ComponentBase.hxx"

namespace ScriptAPI
{
	public value class NameTagComponent : ComponentBase
	{
	public:
		std::string GetName();
		void SetName(std::string value);

		std::string GetTag();
		void SetTag(std::string value);

		bool GetIsActive();
		void SetIsActive(bool value);

		virtual void SetEntityID(TDS::EntityID ID);

	internal:
		NameTagComponent(TDS::EntityID ID);
		TDS::EntityID GetEntityID();

	private:
		property std::string Name
		{
			std::string get();
			void set(std::string value);
		}
		property std::string Tag
		{
			std::string get();
			void set(std::string value);
		}
		property bool IsActive
		{
			bool get();
			void set(bool value);
		}

		TDS::EntityID entityID;
	};
}