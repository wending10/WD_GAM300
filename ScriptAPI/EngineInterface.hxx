// EngineInterface.hxx
#pragma once

#include "Script.hxx"
#include "ecs/ecs.h"

namespace ScriptAPI
{
	public ref class EngineInterface
	{
	public:
		static void HelloWorld();

		static void Init();

		static bool AddScriptViaName(TDS::EntityID entityId, System::String^ scriptName);

		static void ExecuteUpdate();

	private:
		//(^)* reference to managed pointer
		using ScriptList = System::Collections::Generic::List<Script^>;
		static System::Collections::Generic::SortedList<TDS::EntityID,ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		static void updateScriptTypeList();
	};
}