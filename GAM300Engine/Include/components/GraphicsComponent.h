#pragma once
#include "ecs/ecs.h"
#include "ResourceManagement/ResourceManager.h"
namespace TDS
{
	class AssetModel;
	class Texture;

	class GraphicsComponent : public IComponent
	{
	public:
		DLL_API GraphicsComponent();
		DLL_API GraphicsComponent(GraphicsComponent&& toMove) noexcept;
		DLL_API ~GraphicsComponent() = default;

		inline void ToggleRender(bool condition)
		{
			m_ShowMesh = condition;
		}
		inline bool ShowMesh()
		{
			return m_ShowMesh;
		}
		inline TypeReference<AssetModel>& GetAsset()
		{
			return m_AssetReference;
		}
		inline TypeReference<Texture>& GetTexture()
		{
			return m_TextureReference;
		}
		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND

	private:
		TypeReference<AssetModel> m_AssetReference;
		TypeReference<Texture>	m_TextureReference;
		bool m_ShowMesh = true;
		

	};
}