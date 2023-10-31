#include "Rendering/RendererSystem.h"
#include "components/components.h"
#include "Rendering/RenderDataManager.h"
#include "Rendering/Renderer3D.h"
#include "Rendering/GraphicsManager.h"
#include "vulkanTools/VulkanPipeline.h"
#include "vulkanTools/vulkanSwapChain.h"
#include "vulkanTools/VulkanTexture.h"
#include "vulkanTools/Renderer.h"
namespace TDS
{
	struct PushConstantData {
		Mat4 ModelMat{ 1.f };
		Mat4 NormalMat{ 1.f };
	};
	float RendererSystem::lightPosX = 0.f;
	void RendererSystem::OnInit()
	{

	}
	void RendererSystem::OnUpdate(const float dt, const std::vector<EntityID>& entities, Transform* _TransformComponent, GraphicsComponent* _Graphics)
	{
		std::uint32_t frame = GraphicsManager::getInstance().GetSwapchainRenderer().getFrameIndex();

		VkCommandBuffer commandBuffer = GraphicsManager::getInstance().getCommandBuffer();
		for (size_t i = 0; i < entities.size(); ++i)
		{
			Renderer3D::getPipeline()->SetCommandBuffer(commandBuffer);


			if (_Graphics[i].ShowMesh() == true && _Graphics[i].GetAsset().m_ResourcePtr != nullptr)
			{
				if (_Graphics[i].GetAsset().m_ResourcePtr->BufferIsNull())
					_Graphics[i].GetAsset().m_ResourcePtr->CreateBuffers();

				if (Renderer3D::getPipeline()->GetCreateEntry().m_EnableDoubleBuffering)
				{
					GlobalUBO ubo{};
					PushConstantData pushData{};

					if (Vec3 Scale = _TransformComponent[i].GetScale(); Scale.x <= 0.f || Scale.y <= 0.f || Scale.z <= 0.f) {
					}
					else {
						_TransformComponent[i].GenerateTransfom();
					}
					Mat4 temp = _TransformComponent[i].GetTransformMatrix();
					pushData.ModelMat = temp;

					temp.transpose();
					//temp.inverse();
					pushData.NormalMat = temp;

					ubo.m_View = GraphicsManager::getInstance().GetCamera().GetViewMatrix();
					ubo.m_vPointLights[0].m_Position = Vec4(lightPosX, 0.5f, 0.f, 0.2f);
					ubo.m_vPointLights[0].m_Color = Vec4(1.f, 1.f, 1.f, 1.f);
					ubo.m_Projection = Mat4::Perspective(GraphicsManager::getInstance().GetCamera().m_Fov * Mathf::Deg2Rad,
						GraphicsManager::getInstance().GetSwapchainRenderer().getAspectRatio(), 0.1f, 10.f);
					ubo.m_Projection.m[1][1] *= -1;

					Renderer3D::getPipeline()->BindPipeline();
					if (_Graphics[i].GetTexture().m_ResourcePtr != nullptr)
					{
						Renderer3D::getPipeline()->UpdateTexture(4,
							VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
							*_Graphics[i].GetTexture().m_ResourcePtr->m_VulkanTexture);
					}

					Renderer3D::getPipeline()->UpdateUBO(&ubo, sizeof(GlobalUBO), 0, frame);
					Renderer3D::getPipeline()->SubmitPushConstant(&pushData, sizeof(PushConstantData), SHADER_FLAG::VERTEX | SHADER_FLAG::FRAGMENT);

					Renderer3D::getPipeline()->BindVertexBuffer(*_Graphics->GetAsset().m_ResourcePtr->GetVertexBuffer());
					Renderer3D::getPipeline()->BindIndexBuffer(*_Graphics->GetAsset().m_ResourcePtr->GetIndexBuffer());
					Renderer3D::getPipeline()->DrawIndexed(*_Graphics->GetAsset().m_ResourcePtr->GetVertexBuffer(),
						*_Graphics->GetAsset().m_ResourcePtr->GetIndexBuffer(),
						frame);
				}
			}
		}
	}
	void RendererSystem::OnRender(const float dt, const std::vector<EntityID>& entities, GraphicsComponent* _Graphics)
	{
	}

}