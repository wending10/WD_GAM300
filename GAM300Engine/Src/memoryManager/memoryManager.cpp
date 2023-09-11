#include "memoryManager/memoryManager.h"

namespace TDS
{
	// Unique pointer to instance of Scene
	std::unique_ptr<MemoryManager> MemoryManager::m_instance;

	/*!*************************************************************************
	Returns an instance of the MemoryManager
	****************************************************************************/
	std::unique_ptr<MemoryManager>& MemoryManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<MemoryManager>();
		}
		return m_instance;
	}

	void MemoryManager::setNumberOfComponent(std::uint32_t _numberOfComponents)
	{
		numberOfComponents = _numberOfComponents;
	}

	void MemoryManager::newBook()
	{
		BookData newbook;
		newbook.reservedSize.reserve(numberOfComponents);
		newbook.usedSize.reserve(numberOfComponents);
		newbook.endOfComponent.reserve(numberOfComponents);

		books.emplace_back(newbook);
	}

	unsigned char* MemoryManager::newPage(std::uint32_t archetypeID, std::uint32_t componentID)
	{
		if (archetypeID >= books.size()) // book does not exist
		{
			return nullptr;
		}

		books[archetypeID].reservedSize[componentID] = PAGE_SIZE;
		books[archetypeID].usedSize[componentID] = 0;

		unsigned char* pointer = reserve(PAGE_SIZE);

		books[archetypeID].endOfComponent[componentID] = pointer;

		return pointer;
	}

	unsigned char* MemoryManager::resizePage(std::uint32_t archetypeID, std::uint32_t componentID)
	{
		if (archetypeID >= books.size()) // book does not exist
		{
			return nullptr;
		}

		books[archetypeID].reservedSize[componentID] = books[archetypeID].reservedSize[componentID] + PAGE_SIZE;

		unsigned char* pointer = reserve(books[archetypeID].reservedSize[componentID]);

		return pointer;
	}

	void MemoryManager::commitBook(std::uint32_t archetypeID, std::vector<unsigned char*>& componentData)
	{
		int componentNumber = 0;
		for (unsigned char* pointer : componentData)
		{
			commit(pointer, books[archetypeID].usedSize[componentNumber]);
			++componentNumber;
		}
	}

	void MemoryManager::reserveComponentSpace(std::uint32_t archetypeID, std::uint32_t componentID, std::uint32_t componentDataSpace)
	{

	}

	void MemoryManager::freeComponentSpace(std::uint32_t archetypeID, std::uint32_t componentID, std::uint32_t componentDataSpace)
	{

	}

	void MemoryManager::addComponentData(std::uint32_t archetypeID, std::uint32_t componentID, unsigned char* startingComponentPointer, unsigned char* newComponentData)
	{

	}

	void MemoryManager::moveComponentData(std::uint32_t oldArchetypeID, std::uint32_t newArchetypeID, std::uint32_t componentID)
	{

	}

	void MemoryManager::removeComponentData()
	{

	}

	// VirtualAlloc functions
	unsigned char* MemoryManager::reserve(std::uint32_t newPageSize)
	{
		return nullptr; // reinterpret_cast<unsigned char*>(VirtualAlloc(nullptr, newPageSize, MEM_RESERVE, PAGE_READWRITE));
	}

	void MemoryManager::commit(unsigned char* startingPointer, std::uint32_t usedSize)
	{
		//VirtualAlloc(startingPointer, usedSize, MEM_COMMIT, PAGE_READWRITE);
	}

	void MemoryManager::decommit(unsigned char* pointer, std::uint32_t componentSize)
	{
		//VirtualFree(pointer, componentSize, MEM_DECOMMIT);
	}

	void MemoryManager::release(unsigned char* startingPointer, std::uint32_t reservedSize)
	{
		//VirtualFree(startingPointer, reservedSize, MEM_RELEASE);
	}
}
