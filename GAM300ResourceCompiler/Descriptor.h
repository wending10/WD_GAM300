#pragma once
#include "pch.h"
namespace TDS
{

	struct Descriptor
	{
		struct Transform
		{
			float m_Scale[3] = { 1.f, 1.f, 1.f };
			float m_Rotate[3] = { 0.f, 0.f, 0.f };
			float m_Translate[3] = { 0.f, 0.f, 0.f };
		};

		struct Desc
		{
			std::string m_FilePath;
			Transform m_L2W;
			bool MergeMesh = false;
			std::string m_MeshFileName;
			std::string m_RenamedMesh;
		};
		Desc m_Descriptor;
		bool Serialize(std::string_view FilePath, bool Read);
	};

}