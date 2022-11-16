#pragma once
#include <iostream>

template<typename T>
class DynamicArray
{
private:

	T* data;
	size_t used;
	size_t capacity;

public:

	DynamicArray();
	DynamicArray(size_t size);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	~DynamicArray();

public:

	void push_back(const T element);
	void pop_back();
	T& back() const;
	size_t size() const;
	size_t get_capacity() const;
	T& operator[](size_t index);
	T& at(size_t index);
	bool empty() const;
	void resize(size_t n);
	void reserve(size_t n);
	void shrink_to_fit();
	void print() const;

private:

	void copy(const DynamicArray& other);
	void erase();

};

template<typename T>
inline DynamicArray<T>::DynamicArray() : data(nullptr), used(0), capacity(0)
{
};

template<typename T>
inline DynamicArray<T>::DynamicArray(size_t size) : data(new T[size]), used(0), capacity(size)
{
};

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	init(other);
};

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (other != this)
	{
		erase();
		copy(other);
	}
	return *this;
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	erase();
};

template<typename T>
inline void DynamicArray<T>::push_back(const T element)
{
	if (used + 1 > capacity)
	{
		resize(capacity);
	}
		data[used] = element;
		++used;
	
}

template<typename T>
inline void DynamicArray<T>::pop_back()
{
	if (used > 0)
	{
		used--;
	}
	else
	{
		throw std::out_of_range;
	}
}

template<typename T>
inline void DynamicArray<T>::print() const
{
	for (size_t i = 0; i < used; i++)
	{
		std::cout << data[i] << " ";
	}
}

template<typename T>
inline void DynamicArray<T>::resize(size_t n)
{
	if (n == capacity)
	{
		n *= 2;
	}
	T* buffer = new T[n];
	try
	{
		if (n < used)
		{
			used = n;
		}
		for (size_t i = 0; i < used; i++)
		{
			buffer[i] = data[i];
		}
		delete[] data;
		data = buffer;
		capacity = n;
	}
	catch (const std::exception& ex)
	{
		delete[] buffer;
		throw ex.what();
	}	
}

template<typename T>
inline void DynamicArray<T>::reserve(size_t n)
{
	if (n > capacity)
	{
		resize(n);
	}
}

template<typename T>
inline void DynamicArray<T>::shrink_to_fit()
{
	resize(used);
}

template<typename T>
inline size_t DynamicArray<T>::size() const
{
	return used;
}

template<typename T>
inline size_t DynamicArray<T>::get_capacity() const
{
	return capacity;
}

template<typename T>
inline T& DynamicArray<T>::operator[](size_t index)
{
	return data[index];
}

template<typename T>
inline T& DynamicArray<T>::at(size_t index)
{
	if (index >= used)
		throw std::out_of_range;
	return data[index];
}

template<typename T>
inline bool DynamicArray<T>::empty() const
{
	return used == 0;
}

template<typename T>
inline T& DynamicArray<T>::back() const
{
	return data[used-1];
}

template<typename T>
inline void DynamicArray<T>::erase()
{
	delete[] data;
}

template<typename T>
inline void DynamicArray<T>::copy(const DynamicArray& other)
{
	try
	{
		data = new T[other.capacity];
	}
	catch (std::exception ex)
	{
		throw ex.what();
	}
	try
	{
		for (size_t i = 0; i < other.used; i++)
		{
			data[i] = other.data[i];
		}
		used = other.used;
		capacity = other.capacity;
	}
	catch (std::exception ex)
	{
		erase();
		throw ex.what();
	}
}