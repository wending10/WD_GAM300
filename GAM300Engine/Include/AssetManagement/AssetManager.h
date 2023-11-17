#pragma once
/*!*************************************************************************
****
\file AssetManager.h
\author Ho Shu Sheng Eugene
\par DP email: shushengeugene.ho@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Function definitions of the Pipeline Class
****************************************************************************
***/
#include "AssetManagement/ModelFactory.h"
#include "TextureFactory.h"
#include "FontFactory.h"
#include "dotnet/ImportExport.h"
#include "ResourceAllocator.h"

namespace TDS
{

	class AssetManager
	{
	public:
		DLL_API AssetManager();
		DLL_API ~AssetManager();
		void DLL_API Init();
		void DLL_API PreloadAssets();
		void DLL_API ShutDown();

		template <typename T>
		void LoadAsset(std::string_view FilePath, TypeReference<T>& ref)
		{
			AssetFactory<T>::GetInstance().Load(FilePath, ref);
		}
		template <typename T>
		AssetFactory<T>& GetFactory()
		{
			return AssetFactory<T>::GetInstance();
		}


		//inline ResourceAllocator& getResourceAllocator()
		//{
		//	return m_ResourceAllocator;
		//}
		static DLL_API std::shared_ptr<AssetManager> GetInstance();


	private:
		inline static std::shared_ptr<AssetManager> m_Instance = nullptr;



	};
}