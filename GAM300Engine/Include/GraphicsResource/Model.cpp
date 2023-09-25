#include "Model.h"
#include "Geom.h"
#include <fstream>
#include <iostream>
namespace TDS
{
	void Model::DeserializeGeom(GeomCompiled& geomOut, std::string_view PathData)
	{
		std::ifstream inFile(PathData.data(), std::ios::binary);
		if (!inFile)
		{
			std::cerr << "ERROR: Could not open file for reading!\n";
			return;
		}

		auto deserializeVec3 = [](std::ifstream& in, Vec3& vec) {
			in.read(reinterpret_cast<char*>(&vec.x), sizeof(vec.x));
			in.read(reinterpret_cast<char*>(&vec.y), sizeof(vec.y));
			in.read(reinterpret_cast<char*>(&vec.z), sizeof(vec.z));
		};

		auto deserializeVec2 = [](std::ifstream& in, Vec2& vec) {
			in.read(reinterpret_cast<char*>(&vec.x), sizeof(vec.x));
			in.read(reinterpret_cast<char*>(&vec.y), sizeof(vec.y));
		};

		auto deserializeMesh = [](std::ifstream& in, GeomCompiled::Mesh& mesh) {
			in.read(reinterpret_cast<char*>(&mesh.m_Name), sizeof(mesh.m_Name));
		};

		auto deserializeSubMesh = [](std::ifstream& in, GeomCompiled::SubMesh& subMesh) {
			in.read(reinterpret_cast<char*>(&subMesh.m_nFaces), sizeof(subMesh.m_nFaces));
			in.read(reinterpret_cast<char*>(&subMesh.m_iIndices), sizeof(subMesh.m_iIndices));
			in.read(reinterpret_cast<char*>(&subMesh.m_iVertices), sizeof(subMesh.m_iVertices));
			in.read(reinterpret_cast<char*>(&subMesh.m_nVertices), sizeof(subMesh.m_nVertices));
			in.read(reinterpret_cast<char*>(&subMesh.m_iMaterial), sizeof(subMesh.m_iMaterial));
		};

		auto deserializeExtraVertices = [&](std::ifstream& in, GeomCompiled::ExtraVertices& extraVertices) {
			deserializeVec2(in, extraVertices.m_UV);
			deserializeVec3(in, extraVertices.m_Normal);
			deserializeVec3(in, extraVertices.m_Tanget);
			deserializeVec3(in, extraVertices.m_Bitangent);
			in.read(reinterpret_cast<char*>(&extraVertices.m_Colour), sizeof(extraVertices.m_Colour));
		};

		uint32_t meshSize;
		inFile.read(reinterpret_cast<char*>(&meshSize), sizeof(meshSize));
		geomOut.m_Mesh.resize(meshSize);
		for (auto& mesh : geomOut.m_Mesh)
		{
			deserializeMesh(inFile, mesh);
		}

		uint32_t subMeshSize;
		inFile.read(reinterpret_cast<char*>(&subMeshSize), sizeof(subMeshSize));
		geomOut.m_SubMesh.resize(subMeshSize);
		for (auto& subMesh : geomOut.m_SubMesh)
		{
			deserializeSubMesh(inFile, subMesh);
		}

		uint32_t posSize;
		inFile.read(reinterpret_cast<char*>(&posSize), sizeof(posSize));
		geomOut.m_Pos.resize(posSize);
		for (auto& pos : geomOut.m_Pos)
		{
			deserializeVec3(inFile, pos);
		}

		uint32_t extraSize;
		inFile.read(reinterpret_cast<char*>(&extraSize), sizeof(extraSize));
		geomOut.m_Extra.resize(extraSize);
		for (auto& extra : geomOut.m_Extra)
		{
			deserializeExtraVertices(inFile, extra);
		}

		uint32_t indicesSize;
		inFile.read(reinterpret_cast<char*>(&indicesSize), sizeof(indicesSize));
		geomOut.m_Indices.resize(indicesSize);
		inFile.read(reinterpret_cast<char*>(geomOut.m_Indices.data()), indicesSize * sizeof(uint32_t));

		inFile.close();
	}

	void Model::LoadGeomData(GeomCompiled& geom)
	{
		m_VertexData.resize(geom.m_Pos.size());
		m_IndexData.resize(geom.m_Indices.size());
		std::copy(geom.m_Indices.begin(), geom.m_Indices.end(), m_IndexData.data());
		for (size_t i = 0; i < geom.m_Pos.size(); ++i) {
			m_VertexData[i].m_Pos = geom.m_Pos[i];


			if (i < geom.m_Extra.size()) 
			{
				m_VertexData[i].m_UV = geom.m_Extra[i].m_UV;

				m_VertexData[i].m_fNormal = Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f);
				m_VertexData[i].m_fTanget = geom.m_Extra[i].m_Tanget;
				m_VertexData[i].m_fBitangent = geom.m_Extra[i].m_Bitangent;

				m_VertexData[i].m_Color = iColor(geom.m_Extra[i].m_Colour);

				m_VertexData[i].m_Tangent = iColor(Vec4(geom.m_Extra[i].m_Tanget.x, geom.m_Extra[i].m_Tanget.y, geom.m_Extra[i].m_Tanget.z, 1.0f));
				m_VertexData[i].m_Bitangent = iColor(Vec4(geom.m_Extra[i].m_Bitangent.x, geom.m_Extra[i].m_Bitangent.y, geom.m_Extra[i].m_Bitangent.z, 1.0f));
				m_VertexData[i].m_Normal = iColor(Vec4(geom.m_Extra[i].m_Normal.x, geom.m_Extra[i].m_Normal.y, geom.m_Extra[i].m_Normal.z, 1.0f));
			}
		}
	}
	Model::Model()
	{
	}
	Model::~Model()
	{
	}
	void Model::LoadModelData(std::string_view path)
	{
		GeomCompiled geom{};
		DeserializeGeom(geom, path);
		LoadGeomData(geom);

		
	}
	std::vector<VertexData>& Model::GetVertexData()
	{
		return m_VertexData;
	}
	std::vector<std::uint32_t>& Model::GetIndexData()
	{
		return m_IndexData;
	}
}