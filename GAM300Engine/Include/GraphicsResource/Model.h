#pragma once
#include <string_view>
#include "VertexInfo.h"
#include <vector>
#include "Geometry.h"
namespace TDS
{
	struct GeomCompiled;
	class Model
	{
		private:
			
			void DeserializeGeom(GeomCompiled& geom, std::string_view PathData);
			void LoadGeomData(GeomCompiled& geom);
			//This is for testing, we might render mesh by mesh instead of a whole mesh
			std::vector<VertexData> m_VertexData;
			std::vector<std::uint32_t> m_IndexData;
			//Debug draw
			AABB BoundingBox;
		public:
			Model();
			~Model();
			void LoadModelData(std::string_view path);
			std::vector<VertexData>& GetVertexData();
			std::vector<std::uint32_t>& GetIndexData();
		
	};


}