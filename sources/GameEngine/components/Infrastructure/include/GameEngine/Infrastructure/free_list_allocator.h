#ifndef FREE_LIST_ALLOCATOR_H
#define FREE_LIST_ALLOCATOR_H

#include <cstddef>
#include <type_traits>
#include <vector>

#include "GameEngine/Utility/common.h"


GE_BEGIN_ENGINE_NAMESPACE

namespace impl {
template<class T,
    bool = std::is_copy_constructible<T>::value,
    bool = std::is_move_constructible<T>::value,
    bool = std::is_trivially_destructible<T>::value
>
struct Block;
} // namespace impl

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
    static const Handle HandleUndefined;

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

    Size Capacity() const {
        return blockPool.capacity();
    }

private:
    using Block = impl::Block<T>;
    using BlockPool = std::vector<Block>;

    BlockPool blockPool;
    Handle firstFreeBlockIndex;
};


template<class T>
const typename FreelistAllocator<T>::Handle
    FreelistAllocator<T>::HandleUndefined { -1u };


namespace impl {

/*
Remember to undef these macros later in file!
*/

#define GE_impl_GENERATE_FREELIST_BLOCK_DATA(Type) \
    bool used; \
    union { \
        typename FreelistAllocator<Type>::Handle nextAvailableBlockIndex; \
        Type userData; \
    };

#define GE_impl_GENERATE_FREELIST_BLOCK_CTOR(Type) \
    Block() : \
        used(false), \
        nextAvailableBlockIndex(FreelistAllocator<T>::HandleUndefined) \
    {}

#define GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR(Type) \
    Block(const Block& other) : \
        used(other.used) \
    { \
        if (other.used == true) { \
            ::new (&userData) T(other.userData); \
        } else { \
            nextAvailableBlockIndex = other.nextAvailableBlockIndex; \
        } \
    }

#define GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR(Type) \
    Block(Block&& other) : \
        used(std::move(other.used)) \
    { \
        if (other.used == true) { \
            ::new (&userData) T(std::move(other.userData)); \
        } else { \
            nextAvailableBlockIndex = std::move( \
                other.nextAvailableBlockIndex); \
        } \
    }

#define GE_impl_GENERATE_FREELIST_BLOCK_DTOR(Type) \
    ~Block() { \
        if (used == true) { \
            userData.~Type(); \
        } \
    }

template<class T>
struct Block<T, true, true, true> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR(T)
    ~Block() = default;
};

template<class T>
struct Block<T, true, true, false> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_DTOR(T)
};

template<class T>
struct Block<T, true, false, true> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR(T)
    Block(Block&& other) = delete;
    ~Block() = default;
};

template<class T>
struct Block<T, true, false, false> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR(T)
    Block(Block&& other) = delete;
    GE_impl_GENERATE_FREELIST_BLOCK_DTOR(T)
};

template<class T>
struct Block<T, false, true, true> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    Block(const Block& other) = delete;
    GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR(T)
    ~Block() = default;
};

template<class T>
struct Block<T, false, true, false> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    Block(const Block& other) = delete;
    GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR(T)
    GE_impl_GENERATE_FREELIST_BLOCK_DTOR(T)
};

template<class T>
struct Block<T, false, false, true> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    Block(const Block& other) = delete;
    Block(Block&& other) = delete;
    ~Block() = default;
};

template<class T>
struct Block<T, false, false, false> {
    GE_impl_GENERATE_FREELIST_BLOCK_DATA(T)
    GE_impl_GENERATE_FREELIST_BLOCK_CTOR(T)
    Block(const Block& other) = delete;
    Block(Block&& other) = delete;
    GE_impl_GENERATE_FREELIST_BLOCK_DTOR(T)
};

#undef GE_impl_GENERATE_FREELIST_BLOCK_DATA
#undef GE_impl_GENERATE_FREELIST_BLOCK_CTOR
#undef GE_impl_GENERATE_FREELIST_BLOCK_COPY_CTOR
#undef GE_impl_GENERATE_FREELIST_BLOCK_MOVE_CTOR
#undef GE_impl_GENERATE_FREELIST_BLOCK_DTOR

} // namespace impl

GE_END_ENGINE_NAMESPACE

#endif // FREE_LIST_ALLOCATOR_H
