#include "imguiHelper/ImguiAssetBrowser.h"

namespace TDS
{
	AssetBrowser::AssetBrowser()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Asset Browser";
		windowPadding = ImVec2(0.f, 0.f);

		//insertEntities();
	}
	static const std::filesystem::path s_TextureDirectory = "assets/";
	void AssetBrowser::update()
	{
	m_curr_path = "../assets/";
		if (m_curr_path != std::filesystem::path(s_TextureDirectory))
		{
			if (ImGui::Button("<-")) //will only show if u went into a folder in the current directory above
			{
				m_curr_path = m_curr_path.parent_path();
			}
		}
		//float cellSize = thumbnail_size + padding;

		//float panelWidth = ImGui::GetContentRegionAvail().x;
		//float columnCount = (int)(panelWidth / cellSize);
		ImGui::Columns(5, 0, false);

		for (auto& directory_entry : std::filesystem::directory_iterator(m_curr_path))
		{
			path1 = directory_entry.path().string();
			auto relative_path = std::filesystem::relative(directory_entry.path(), s_TextureDirectory);

			//ImGui::Button(path1.c_str(), { thumbnail_size, thumbnail_size });
			//shorten the 
			ImGui::Text(path1.c_str());

			if (ImGui::Button(path1.c_str(), { thumbnail_size, thumbnail_size }) && ImGui::IsMouseDragging(0))
			{
				selectedpath = path1;
				//AddLog("the directory im clicking is: ");
				//AddLog(selectedpath.c_str());
				//ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern);
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
				{
					//AddLog("begin dragging");
					ImGui::SetDragDropPayload("path", path1.c_str(), 1);
					ImGui::Text(selectedpath.c_str());

					ImGui::EndDragDropSource();

				}
			}
			/*if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceExtern))
			{
				ImGui::SetDragDropPayload("path", path1.c_str(), 1);
				ImGui::Text(path1.c_str());
				if (!ImGui::IsMouseDown(0))
				{
					ImGui::EndDragDropSource();

				}
			}

			if (ImGui::BeginDragDropTarget())
			{
				ImGui::EndDragDropTarget();
			}*/
			ImGui::NextColumn();
		}


		ImGui::Columns(1);
		ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);


	}
}