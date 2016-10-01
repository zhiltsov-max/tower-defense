#ifndef FREE_LIST_ALLOCATOR_H
#define FREE_LIST_ALLOCATOR_H

#include <vector>
#include <cstddef>

namespace GE {

template<class T>
class FreelistAllocator
{
public:
    using Size = std::size_t;
    using Difference = std::ptrdiff_t;
    using Index = std::size_t;
    using Pointer = T*;
    using ConstPointer = const T*;
    static constexpr Index UndefinedIndex { -1u };

    FreelistAllocator(Size initialCapacity = 0) :
        blockPool(),
        firstFreeBlockIndex(UndefinedIndex)
    {
        if (initialCapacity == 0) {
            return;
        }

        blockPool.resize(initialCapacity);
        firstFreeBlockIndex = 0;

        auto it = blockPool.begin();
        const auto iend = --blockPool.end();
        for (; it != iend; ++it) {
            it->used = false;
            it->data.nextAvailableBlockIndex = it - blockPool.begin() + 1;
        }
        it->used = false;
        it->data.nextAvailableBlockIndex = UndefinedIndex;
    }
    FreelistAllocator(const FreelistAllocator& other) = delete;
    FreelistAllocator(FreelistAllocator&& other) = default;
    FreelistAllocator& operator = (const FreelistAllocator& other) = delete;
    FreelistAllocator& operator = (FreelistAllocator&& other) = default;

    Index Allocate() {
        if (firstFreeBlockIndex == UndefinedIndex) {
            blockPool.emplace_back();
            blockPool.back().used = false;
            blockPool.back().data.nextAvailableBlockIndex = UndefinedIndex;
            firstFreeBlockIndex = blockPool.size() - 1;
        }

        Block& block = blockPool[firstFreeBlockIndex];
        const auto blockIndex = firstFreeBlockIndex;
        firstFreeBlockIndex = block.data.nextAvailableBlockIndex;
        block.used = true;
        return blockIndex;
    }

    void Deallocate(Index index) {
        if (Owns(index) == false) {
            return;
        }
        Block* block = GetOwningBlock(index);
        block->used = false;
        block->data.nextAvailableBlockIndex = firstFreeBlockIndex;
        firstFreeBlockIndex = index;
    }

    bool Owns(Index index) const {
        return (0 <= index) && (index < blockPool.size()) &&
            (GetOwningBlock(index)->used == true);
    }

    ConstPointer GetElementDataPointer(Index index) const {
        if (Owns(index) == false) {
            return nullptr;
        }
        return &blockPool[index].data.userData;
    }

    Pointer GetElementDataPointer(Index index) {
        if (Owns(index) == false) {
            return nullptr;
        }
        return &blockPool[index].data.userData;
    }

private:

    struct Block {
        union BlockData {
            Index nextAvailableBlockIndex;
            T userData;

            constexpr BlockData() : nextAvailableBlockIndex(UndefinedIndex) {}
        };

        bool used;
        BlockData data;

        constexpr Block() : used(false), data() {}
    };
    using BlockPool = std::vector<Block>;

    BlockPool blockPool;
    Index firstFreeBlockIndex;

    const Block* GetOwningBlock(Index index) const {
        return &blockPool[index];
    }

    Block* GetOwningBlock(Index index) {
        return &blockPool[index];
    }
};

template <class T, class U>
bool operator == (const FreelistAllocator<T>&, const FreelistAllocator<U>&) {
    return false;
}

template <class T, class U>
bool operator != (const FreelistAllocator<T>&, const FreelistAllocator<U>&) {
    return false;
}

} // namespace GE

#endif // FREE_LIST_ALLOCATOR_H
