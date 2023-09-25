#pragma once
#include <array>
#include <unordered_map>
#include <string>
#include <shared_mutex>
#include <functional>
#include "ResourceRef.h"
#include "../Identifier/Identifier.h"
#include <assert.h>
namespace TDS
{

	/*
		TODO: to be fixed
	*/
	
	constexpr std::int32_t MAX_RESOURCES = 1024;





	struct UniversalType
	{
		TypeIdentifier m_Identifier;
		const char* m_pName;
		void(*m_DestroyFunc)(void*);
		void(*m_LoadFunc);
	};

	struct Instance_info
	{
		void* m_pData{ nullptr };
		UniqueID m_GUID;
		TypeIdentifier m_Type;
		std::int32_t m_RefCount{1};
	};
	


	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		template <typename ...Types>
		void RegisterTypes()
		{
			auto registerSingleType = [this]<typename T>()
			{
				TypeIdentifier identifier;
				T tInst{};
				identifier.CreateTypeID(tInst);

				UniversalType universalType;
				universalType.m_Identifier = identifier;
				universalType.m_pName = getTypeName<decltype(tInst)>().c_str();
				universalType.m_LoadFunc = nullptr;
				universalType.m_DestroyFunc = nullptr;

				m_AllowedTypes.emplace(identifier.m_TypeHash, universalType);
			};

			(registerSingleType.operator()<Types>(), ...);
		}

		//template <typename T>
		//T* getResource(SingleTypeReference<T>& ref)
		//{
		//	if (ref.IsPointer()) return ref.m_Reference;

		//	GuidTypeIDKey key(ref.m_GUID, ref.m_Identifier);
		//	auto found = m_ResourceInstance.find(key);
		//	if (found != m_ResourceInstance.end())
		//	{
		//		auto& entry = found->second;
		//		++entry->m_RefCount;
		//		ref.m_Reference = reinterpret_cast<T*>(entry->m_pData);
		//		return ref.m_Reference;
		//	}
		//	T* pResource = TypeLoader<T>::Create();

		//	if (pResource == 0) return 0;

		//	ref.m_Reference = pResource;
		//	return ref.m_Reference;
		//}


		//template <typename T>
		//void ReleaseReference(SingleTypeReference<T>& ref)
		//{
		//	if (ref.IsPointer() == false || ref.m_GUID.GetUniqueID() == 0) return;

		//	auto refToUsedResc = m_ResourceInUsed.find(reinterpret_cast<std::uint64_t>(ref.IsPointer));
		//	assert(m_AllowedTypes.find(ref.m_Identifier.m_TypeHash) != m_AllowedTypes.end());

		//	auto& refToOriginalRes = *refToUsedResc->second;
		//	--ref.m_RefCount;
		//	UniqueID OriginalId = refToOriginalRes.m_GUID;
		//	assert(refToOriginalRes.m_Type.m_TypeHash == ref.m_Identifier.m_TypeHash);
		//	assert(refToOriginalRes.m_pData == reinterpret_cast<void*>(ref.m_Reference));

		//	if (refToOriginalRes.m_RefCount == 0)
		//	{
		//		TypeLoader<T>::Destroy(ref.m_Reference);
		//		//ResourceResourceInfo(refToOriginalRes);
		//	}
		//	ref.m_GUID = OriginalId;
		//}

		//template <typename T>
		//UniqueID GetInstanceGuid(const SingleTypeReference<T>& ref) const
		//{
		//	if (!ref.m_Reference.IsPointer())
		//		return ref.m_GUID;
		//	auto instance = m_ResourceInUsed.find(reinterpret_cast<std::uint64_t>(ref.m_Reference));
		//	assert(instance != m_ResourceInUsed.end());
		//	return instance->second->m_GUID;
		//}

		//inline std::int32_t GetResouceCount()
		//{
		//	assert(m_ResourceInstance.size() == m_ResourceInUsed.size());

		//	return std::uint32_t(m_ResourceInstance.size());
		//}

		//void* GetResource(UniversalReference& uRef);

		//void ReleaseReference(UniversalReference& uRef);

		//UniqueID getInstanceGUID(UniversalReference& uRef) const;

		//void ReleaseResource(Instance_info& resourceInfo);

		//Instance_info& AllocResource();

		//void InstanceInfoAlloc(void* pResourceData, UniqueID guid, TypeIdentifier typeID);

		//void InstanceInfoRelease(Instance_info& resourceInfo);





	private:
		std::shared_ptr<std::shared_mutex> m_MultiAccessMutex;
		//Key is typeID
		std::unordered_map<std::uint64_t, UniversalType> m_AllowedTypes;
		std::unordered_map<GuidTypeIDKey, Instance_info*, CombineHash> m_ResourceInstance;
		//Key is pointer address
		std::unordered_map<std::uint64_t, Instance_info*> m_ResourceInUsed;
		std::array<Instance_info, MAX_RESOURCES> m_InfoBuffer;
		Instance_info* m_pEmptyBuffer = nullptr;

	};
}