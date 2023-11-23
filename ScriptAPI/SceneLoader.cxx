#include "SceneLoader.hxx"

namespace ScriptAPI
{
	void SceneLoader::LoadMainMenu()
	{
		TDS::SceneManager::GetInstance()->loadScene("../assets/scenes/Development Main Menu.json");
	}
	void SceneLoader::LoadMainGame()
	{
		TDS::SceneManager::GetInstance()->loadScene("../assets/scenes/Development Game (2).json");
	}
}