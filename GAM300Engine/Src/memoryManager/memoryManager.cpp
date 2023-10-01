#include <windows.h>

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

	// shld be called in register component
	// increment number of components

	// New Archetype
	void MemoryManager::newBook(const ArchetypeID& archetypeID)
	{
		BookData newbook;
		newbook.reservedSize.resize(numberOfComponents);
		newbook.usedSize.resize(numberOfComponents);
		newbook.committedSize.resize(numberOfComponents);
		newbook.startOfComponent.resize(numberOfComponents);

		books[archetypeID] = newbook;
	}

	// New Component in Archetype
	unsigned char* MemoryManager::newPage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		if (books.find(archetypeID) == books.end()) // book does not exist
		{
			return nullptr;
		}

		books[archetypeID].reservedSize[componentID] = PAGE_SIZE;
		books[archetypeID].usedSize[componentID] = 0;
		books[archetypeID].committedSize[componentID] = 0;

		unsigned char* pointer = reserve(PAGE_SIZE);

		books[archetypeID].startOfComponent[componentID] = pointer;

		return pointer;
	}

	void MemoryManager::resizePage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		if (books.find(archetypeID) == books.end()) // book does not exist
		{
			return;
		}

		books[archetypeID].reservedSize[componentID] += PAGE_SIZE;

		reserve(books[archetypeID].reservedSize[componentID], books[archetypeID].startOfComponent[componentID]);
	}

	void MemoryManager::commitBook(const ArchetypeID& archetypeID)
	{
		int componentID = 0;
		for (int componentID = 0; componentID < archetypeID.size(); ++componentID)
		{
			if (archetypeID[componentID] == '0')
			{
				continue;
			}

			commit(books[archetypeID].committedSize[componentID], books[archetypeID].startOfComponent[componentID]);
		}
	}

	void MemoryManager::commitPage(const ArchetypeID& archetypeID, std::uint32_t componentID)
	{
		commit(books[archetypeID].committedSize[componentID], books[archetypeID].startOfComponent[componentID]);
	}

	void MemoryManager::freeBook(const ArchetypeID& archetypeID)
	{
		int componentID = 0;
		for (int componentID = 0; componentID < archetypeID.size(); ++componentID)
		{
			if (archetypeID[componentID] == '0')
			{
				continue;
			}

			release(books[archetypeID].startOfComponent[componentID]);
		}
	}

	void MemoryManager::freePage(unsigned char* pointer)
	{
		release(pointer);
	}

	// Adding to used space (for committing)
	void MemoryManager::reserveComponentSpace(const ArchetypeID& archetypeID, std::uint32_t componentID, std::uint32_t componentSize)
	{
		books[archetypeID].committedSize[componentID] = componentSize;

		while (books[archetypeID].committedSize[componentID] > books[archetypeID].reservedSize[componentID])
		{
			resizePage(archetypeID, componentID);
		}
	}

	unsigned char* MemoryManager::getComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index)
	{
		if (books[archetypeID].committedSize[componentID] < (index * componentSize))
		{
			return nullptr; // out of memory
		}

		return books[archetypeID].startOfComponent[componentID] + index * componentSize;
	}

	// Adding data after committing
	// Returns pointer to added component
	unsigned char* MemoryManager::addComponentData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize, std::uint32_t index)
	{
		books[archetypeID].usedSize[componentID] += componentSize;

		std::uint32_t& committedSize = books[archetypeID].committedSize[componentID];

		// Add check to make sure there is enough space
		if (committedSize < books[archetypeID].usedSize[componentID])
		{
			// If committedSize is less than the normal page size, then x2, if not then + PAGE_SIZE
			if (committedSize > PAGE_SIZE)
			{
				committedSize += PAGE_SIZE;
			}
			else
			{
				committedSize += committedSize;
			}

			if (books[archetypeID].reservedSize[componentID] < committedSize)
			{
				resizePage(archetypeID, componentID);
			}

			commit(committedSize, books[archetypeID].startOfComponent[componentID]);
		}

		return books[archetypeID].startOfComponent[componentID] + index * componentSize;
	}

	// just to change sizes
	void MemoryManager::removeComponentEndData(ArchetypeID archetypeID, std::uint32_t componentID, std::uint32_t componentSize)
	{
		books[archetypeID].usedSize[componentID] -= componentSize;
	}

	// VirtualAlloc functions
	unsigned char* MemoryManager::reserve(std::uint32_t newPageSize, unsigned char* startingPointer)
	{
		return reinterpret_cast<unsigned char*>(VirtualAlloc(reinterpret_cast<void*>(startingPointer), newPageSize, MEM_RESERVE, PAGE_READONLY));
	}

	unsigned char* MemoryManager::commit(std::uint32_t usedSize, unsigned char* startingPointer)
	{
		return reinterpret_cast<unsigned char*>(VirtualAlloc(reinterpret_cast<void*>(startingPointer), usedSize, MEM_COMMIT, PAGE_READWRITE));
	}

	void MemoryManager::decommit(std::uint32_t componentSize, unsigned char* pointer)
	{
		VirtualFree(reinterpret_cast<void*>(pointer), componentSize, MEM_DECOMMIT);
	}

	void MemoryManager::release(unsigned char* startingPointer)
	{
		VirtualFree(reinterpret_cast<void*>(startingPointer), 0, MEM_RELEASE);
	}
}
