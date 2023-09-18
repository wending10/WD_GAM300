#ifndef MEMORYMANAGER
#define MEMORYMANAGER

#include <cstdint>
#include <vector>
#include <memory>

//#include <memoryapi.h>

namespace TDS
{
	class MemoryManager // for ECS
	{
	public:
		/*!*************************************************************************
		Returns an instance of the MemoryManager
		****************************************************************************/
		static std::unique_ptr<MemoryManager>& GetInstance();

		struct BookData
		{
			std::vector<std::uint32_t> reservedSize;
			std::vector<std::uint32_t> usedSize;
			std::vector<unsigned char*> endOfComponent;
		};

		void setNumberOfComponent(std::uint32_t _numberOfComponents);

		void newBook();
		unsigned char* newPage(std::uint32_t archetypeID, std::uint32_t componentID);
		unsigned char* resizePage(std::uint32_t archetypeID, std::uint32_t componentID);

		void commitBook(std::uint32_t archetypeID, std::vector<unsigned char*>& componentData);

		// Reserving data space to commit
		void reserveComponentSpace(std::uint32_t archetypeID, std::uint32_t componentID, std::uint32_t componentDataSpace);
		void freeComponentSpace(std::uint32_t archetypeID, std::uint32_t componentID, std::uint32_t componentDataSpace);

		// Putting data into committed space
		void addComponentData(std::uint32_t archetypeID, std::uint32_t componentID, unsigned char* startingComponentPointer, unsigned char* newComponentData);
		void moveComponentData(std::uint32_t oldArchetypeID, std::uint32_t newArchetypeID, std::uint32_t componentID);
		void removeComponentData();

	private:
		// Unique pointer to MemoryManager
		static std::unique_ptr<MemoryManager> m_instance;

		const std::uint32_t PAGE_SIZE = 4096;
		std::uint32_t numberOfComponents;

		std::vector<BookData> books;

		// VirtualAlloc functions
		unsigned char* reserve(std::uint32_t newPageSize);
		void commit(unsigned char* startingPointer, std::uint32_t usedSize);
		void decommit(unsigned char* pointer, std::uint32_t componentSize);
		void release(unsigned char* startingPointer, std::uint32_t reservedSize);
	};
}

#endif