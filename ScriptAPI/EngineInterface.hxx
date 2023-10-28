/*!*****************************************************************************
 * \file          EngineInterface.hxx
 * \author        Elton Teo Zhe Wei
 * \par DP email: e.teo@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Entry point for C++/CLI interface for scripting language
 *******************************************************************************/
#pragma once

#include "Script.hxx"



namespace ScriptAPI
{
	public ref class EngineInterface
	{
	public:
		/*!*************************************************************************
		* Initializes the scriptlist for all active entities
		***************************************************************************/
		static void Init();
		/*!*************************************************************************
		* Add Scripts via name in managed script library
		***************************************************************************/
		static bool AddScriptViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Add GameObject to List
		***************************************************************************/
		static bool AddGameObjectViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Updates GameObject Name
		***************************************************************************/
		static bool UpdateGameObjectName(System::String^ oldName, System::String^ newName);
		/*!*************************************************************************
		* Gets Game Object List
		***************************************************************************/
		static System::Collections::Generic::SortedList<System::String^, TDS::EntityID>^ GetGameObjectList();
		/*!*************************************************************************
		* Calls all script awake function
		***************************************************************************/
		static void ExecuteAwake();
		/*!*************************************************************************
		* Calls all script OnEnable function
		***************************************************************************/
		static void ExecuteOnEnable();
		/*!*************************************************************************
		* Toggles active status on script
		***************************************************************************/
		static bool ToggleScriptViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Calls all script start function
		***************************************************************************/
		static void ExecuteStart();
		/*!*************************************************************************
		* Calls all script updates function
		***************************************************************************/
		static void ExecuteUpdate();
		/*!*************************************************************************
		* Calls all script LateUpdate function
		***************************************************************************/
		static void ExecuteLateUpdate();
		/*!*************************************************************************
		* Calls all script OnDisable function
		***************************************************************************/
		static void ExecuteOnDisable();
		/*!*************************************************************************
		* Calls all script OnDestroy function
		***************************************************************************/
		static void ExecuteOnDestroy();
		/*!*************************************************************************
		* Reloads the script assembly
		***************************************************************************/
		static void Reload();
		/*!*************************************************************************
		* Checks if Entity has Script
		***************************************************************************/
		static bool HasScriptViaName(TDS::EntityID entityId, System::String^ scriptName);
		/*!*************************************************************************
		* Returns Script Type
		***************************************************************************/
		static bool GetScript(TDS::EntityID entityId, System::String^ scriptName, rttr::variant& instance);
		/*!*************************************************************************
		* Serializing Stuff
		***************************************************************************/
		static void Serialize(Object^ obj, String^ filename);
		/*!*************************************************************************
		* Remove Entity from scriptList
		***************************************************************************/
		static void RemoveEntity(TDS::EntityID entityId);

		/*static std::vector<std::string> GetTypeListName()*/


	private:
		//(^)* reference to managed pointer
		using ScriptList = System::Collections::Generic::List<Script^>;
		static System::Collections::Generic::SortedList<System::String^, TDS::EntityID>^ gameObjectList;
		static System::Collections::Generic::SortedList<TDS::EntityID, ScriptList^>^ scripts;
		static System::Collections::Generic::IEnumerable<System::Type^>^ scriptTypeList;
		/*!*************************************************************************
		* Updates script Type list
		***************************************************************************/
		static void updateScriptTypeList();
		static System::Runtime::Loader::AssemblyLoadContext^ loadContext;
	};
}