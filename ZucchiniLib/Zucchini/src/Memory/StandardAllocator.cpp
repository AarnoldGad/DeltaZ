#include "zepch.hpp"

#include "zucchini/Memory/StandardAllocator.hpp"
#include "zucchini/Log/Logger.hpp"
#include "zucchini/Log/FileWriter.hpp"
#include "zucchini/Log/ConsoleWriter.hpp"

namespace ze
{
   namespace
   {
      // Identification hashes
      constexpr unsigned int s_allocationHash = 0xA110CA73; // Identify a block allocated with this allocator
      constexpr unsigned int s_releaseHash = 0xF533D; // Identify a block freed

      Logger& MemoryLogger()
      {
         static FileWriter writer("memory.log");
         static Logger logger("StandardAllocator", { &writer, &ConsoleWriter::Get() });

         return logger;
      }
   }

   StandardAllocator& StandardAllocator::GetStandardAllocator()
   {
      static StandardAllocator allocator;

      return allocator;
   }

   StandardAllocator::StandardAllocator()
   : m_blockList{ 0, {nullptr, 0, nullptr}, 0, &m_blockList, &m_blockList } {}

   void* StandardAllocator::allocate(size_t size, SourceLocation const& location)
   {
      Block* allocatedBlock = allocateBlock(size, location);
      initBlock(allocatedBlock, size, location);
      pushBlockToList(allocatedBlock);
      increaseStats(size);
      return reinterpret_cast<uint8_t*>(allocatedBlock) + sizeof(Block);
   }

   size_t StandardAllocator::release(void* pointer, SourceLocation const& location) noexcept
   {
      if (pointer == nullptr) return 0;

      Block* allocatedBlock = retrieveBlock(pointer);
      size_t blockSize = allocatedBlock->size;

      if (!isBlockDeletable(allocatedBlock))
      {
         MemoryLogger().log(Logger::Level::Error, (allocatedBlock->guardHash == s_releaseHash ? "Double deletion" : "Undefined deletion"));

         if (location.file)
            MemoryLogger().logFormatted("\n\tat {}::{}:{}", location.file, location.function, location.line);
         else
            MemoryLogger().log("\n\tat undefined position");

         MemoryLogger().endLine();
         return 0;
      }

      deinitBlock(allocatedBlock);
      popBlockFromList(allocatedBlock);

      std::free(allocatedBlock);

      decreaseStats(blockSize);

      return blockSize;
   }

   StandardAllocator::Block* StandardAllocator::allocateBlock(size_t size, SourceLocation const& location)
   {
      Block* block = static_cast<Block*>(std::malloc(size + sizeof(Block)));

      if (block == nullptr)
      {
         MemoryLogger().logFormatted(Logger::Level::Error, "Unable to allocate {} bytes", size);

         if (location.file)
            MemoryLogger().logFormatted("\n\tat {}::{}:{}", location.file, location.function, location.line);
         else
            MemoryLogger().log("\n\tat undefined position");

         MemoryLogger().endLine();
         throw std::bad_alloc{};
      }

      return block;
   }

   inline StandardAllocator::Block* StandardAllocator::retrieveBlock(void* pointer) noexcept
   {
      return reinterpret_cast<Block*>(static_cast<uint8_t*>(pointer) - sizeof(Block));
   }

   void StandardAllocator::initBlock(Block* block, size_t size, SourceLocation const& location) const noexcept
   {
      block->size = size;
      block->location = location;
      block->guardHash = s_allocationHash;
   }

   inline bool StandardAllocator::isBlockDeletable(Block* block) const noexcept
   {
      if (block->guardHash != s_allocationHash)
         return false;

      return true;
   }

   inline void StandardAllocator::deinitBlock(Block* block) const noexcept
   {
      block->guardHash = s_releaseHash;
   }

   void StandardAllocator::pushBlockToList(Block* block) noexcept
   {
      block->previous = m_blockList.previous;
      block->next = &m_blockList;

      m_blockList.previous->next = block;
      m_blockList.previous = block;
   }

   void StandardAllocator::popBlockFromList(Block* block) noexcept
   {
      block->previous->next = block->next;
      block->next->previous = block->previous;
   }

   void StandardAllocator::increaseStats(size_t size) noexcept
   {
      m_totalAllocations++;
      m_totalMemoryAllocated += size;
   }

   void StandardAllocator::decreaseStats(size_t size) noexcept
   {
      m_totalAllocations--;
      m_totalMemoryAllocated -= size;
   }

   void StandardAllocator::traceLeaks()
   {
      Block* leakedPointer = m_blockList.next;
      while (leakedPointer != &m_blockList)
      {
         if (leakedPointer->location.file)
         {
            MemoryLogger().logLine(Logger::Level::Error, "{} bytes", leakedPointer->size);
            MemoryLogger().logLine("\tat {:x} {}::{}:{}",
                                        reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(leakedPointer) + sizeof(Block)),
                                        leakedPointer->location.file, leakedPointer->location.function, leakedPointer->location.line);
         }

         void* handledLeak = leakedPointer;
         leakedPointer = leakedPointer->next;

         std::free(handledLeak);
      }
   }

   StandardAllocator::~StandardAllocator()
   {
      if (getTotalAllocations() != 0)
      {
         MemoryLogger().logLine(Logger::Level::Debug, "--- Standard Allocator registered {} leaks ! ------", getTotalAllocations());
         MemoryLogger().logLine("--- {} bytes leaked", getTotalMemoryAllocated());

         traceLeaks();
      }
   }
}
