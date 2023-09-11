// EngineInterface.hxx
#pragma once

#include "Script.hxx"

namespace ScriptAPI
{
	public ref class EngineInterface
	{
	public:
		static void HelloWorld();

		static void Init();

		static bool AddScriptViaName(int entityId, System::String^ scriptName);

		static void ExecuteUpdate();

	private:
		//(^)* reference to managed pointer
		using ScriptList = System::Collections::Generic::List<Script^>;
		static System::Collections::Generic::SortedList<int,ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		static void updateScriptTypeList();
	};
}