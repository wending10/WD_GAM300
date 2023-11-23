#include "SceneLoader.hxx"
#include "TypeConversion.hxx"
namespace ScriptAPI
{
	void SceneLoader::LoadMainMenu()
	{
		
		TDS::SceneManager::GetInstance()->loadScene("Development Main Menu");
	}
	void SceneLoader::LoadMainGame()
	{
		TDS::SceneManager::GetInstance()->loadScene("DevelopmentGame");
	}
}