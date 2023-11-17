#include "AssetManagement/AssetManager.h"
#include "AssetManagement/FontFactory.h"

namespace TDS
{

	AssetManager::AssetManager()
	{
	}
	AssetManager::~AssetManager()
	{
	}
	void AssetManager::Init()
	{
	}
	void AssetManager::PreloadAssets()
	{
		AssetFactory<AssetModel>::GetInstance().Preload();
		AssetFactory<Texture>::GetInstance().Preload();
		AssetFactory<FontAtlas>::GetInstance().Preload();

	}

	void DLL_API AssetManager::ShutDown()
	{
		AssetFactory<AssetModel>::GetInstance().DestroyAllModels();
		AssetFactory<Texture>::GetInstance().DestroyAllTextures();

	}

	std::shared_ptr<AssetManager> AssetManager::GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = std::make_shared<AssetManager>();
		return m_Instance;
	}



}