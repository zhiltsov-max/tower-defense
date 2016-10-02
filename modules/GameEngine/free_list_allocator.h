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
    using Handle = std::size_t;
    using Pointer = T*;
    using ConstPointer = const T*;
    using Reference = T&;
    using ConstReference = const T&;
    static constexpr Handle HandleUndefined { -1u };

    FreelistAllocator(Size initialCapacity = 0) :
        blockPool(),
        firstFreeBlockIndex(HandleUndefined)
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
            it->nextAvailableBlockIndex = it - blockPool.begin() + 1;
        }
        it->used = false;
        it->nextAvailableBlockIndex = HandleUndefined;
    }

    Handle Allocate() {
        if (firstFreeBlockIndex == HandleUndefined) {
            blockPool.emplace_back();
            firstFreeBlockIndex = blockPool.size() - 1;
        }

        auto& block = blockPool[firstFreeBlockIndex];
        const auto blockIndex = firstFreeBlockIndex;
        firstFreeBlockIndex = block.nextAvailableBlockIndex;
        block.used = true;
        return blockIndex;
    }

    void Deallocate(Handle index) {
        if (Owns(index) == false) {
            return;
        }
        auto& block = blockPool[index];
        block.used = false;
        block.nextAvailableBlockIndex = firstFreeBlockIndex;
        firstFreeBlockIndex = index;
    }

    bool Owns(Handle index) const {
        return (0 <= index) && (index < blockPool.size()) &&
            (blockPool[index].used == true);
    }

    ConstPointer GetElementPointer(Handle index) const {
        if (Owns(index) == false) {
            return nullptr;
        }
        return &(operator [](index));
    }

    Pointer GetElementPointer(Handle index) {
        if (Owns(index) == false) {
            return nullptr;
        }
        return &(operator [](index));
    }

    ConstReference operator [] (Handle index) const {
        return blockPool[index].userData;
    }

    Reference operator [] (Handle index) {
        return blockPool[index].userData;
    }

private:
    struct Block {
        bool used;

        union {
            Handle nextAvailableBlockIndex;
            T userData;
        };


        Block() :
            used(false),
            nextAvailableBlockIndex(HandleUndefined)
        {}

        Block(const Block& other) :
            used(other.used)
        {
            if (other.used == true) {
                ::new (&userData) T(other.userData);
            } else {
                nextAvailableBlockIndex =
                    other.nextAvailableBlockIndex;
            }
        }

        Block(Block&& other) :
            used(std::move(other.used))
        {
            if (other.used == true) {
                ::new (&userData) T(std::move(other.userData));
            } else {
                nextAvailableBlockIndex = std::move(
                    other.nextAvailableBlockIndex);
            }
        }

        Block& operator = (const Block& other) {
            if (this != &other) {
                if (other.used == true) {
                    if (used == false) {
                        ::new (&userData) T(other.userData);
                    } else {
                        userData = other.userData;
                    }
                } else {
                    nextAvailableBlockIndex =
                        other.nextAvailableBlockIndex;
                }
                used = other.used;
            }
            return *this;
        }

        Block& operator = (Block&& other) {
            if (this != &other) {
                if (other.used == true) {
                    if (used == false) {
                        ::new (&userData) T(std::move(other.userData));
                    } else {
                        userData = std::move(other.userData);
                    }
                } else {
                    nextAvailableBlockIndex = std::move(
                        other.nextAvailableBlockIndex);
                }
                used = std::move(other.used);
            }
            return *this;
        }

        ~Block() {
            if (used == true) {
                userData.~T();
            }
        }
    };
    using BlockPool = std::vector<Block>;

    BlockPool blockPool;
    Handle firstFreeBlockIndex;
};

} // namespace GE

#endif // FREE_LIST_ALLOCATOR_H
