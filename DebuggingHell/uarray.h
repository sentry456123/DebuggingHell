#pragma once

#include <cstddef>

template <typename T>
class DynamicArray
{
public:
	inline DynamicArray(std::size_t size) noexcept
		:
		mSize(size), mRefCount(new std::size_t(1))
	{
		mArray = new T[size];
	}

	inline DynamicArray(const DynamicArray& dynamicArray) noexcept
	{
		CopyFrom(dynamicArray);
	}

	/*! @brief Creates a dynamic array with a raw array pointer
	 *
	 *  the parameter arr will be automatically freed after this
	 *	object is destroyed. There is no need to free arr.
	 *
	 *  @param[in] arr A raw pointer to use.
	 */
	inline DynamicArray(T* arr, std::size_t size) noexcept
		:
		mArray(arr), mSize(size), mRefCount(new std::size_t(1))
	{}

	inline virtual ~DynamicArray(void) noexcept
	{
		(*mRefCount)--;
		if (*mRefCount == 0) {
			delete mArray;
			delete mRefCount;
		}
	}

	inline std::size_t Size(void) noexcept
	{
		return mSize;
	}

	inline std::size_t ByteSize(void) noexcept
	{
		return mSize * sizeof(T);
	}

	inline T* Data(void) noexcept
	{
		return mArray;
	}

	inline void operator=(const DynamicArray& dynamicArray) noexcept
	{
		CopyFrom(dynamicArray);
	}

protected:
	inline void CopyFrom(const DynamicArray& dynamicArray) noexcept
	{
		mArray = dynamicArray.mArray;
		mSize = dynamicArray.mSize;
		mRefCount = dynamicArray.mRefCount;
		(*mRefCount)++;
	}

	T* mArray;
	std::size_t mSize;
	std::size_t* mRefCount;

};
