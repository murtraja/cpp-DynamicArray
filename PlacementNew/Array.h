#pragma once
template<typename T>
class CArray
{
	T* m_array{ nullptr };
	int m_size{};
	int m_capacity{};
	
	void ChangeCapacity(int newCapacity)
	{
		if (newCapacity < m_size)
		{
			std::cout << "Can't change the capacity to " << newCapacity << ", since it is less than size " << m_size << ".\n";
		}

		char* newBuffer = new char[sizeof(T)*newCapacity];
		T* newArray = reinterpret_cast<T*>(newBuffer);
		for (int i = 0; i < m_size; i++)
		{
			new(newArray + i) (*(m_array + i)); // copy over
		}

		for (int i = 0; i < m_size; i++)
		{
			(m_array + i)->~T();
		}
		char* oldBuffer = reinterpret_cast<char*>(m_array);
		delete[] oldBuffer;
		m_array = newBuffer;
		m_capacity = newCapacity;
	}

public:
	CArray()
	{

	}

	CArray(int n)
	{
		/*
		the idea here is to create an array of n default Ts
		if we do it iteratively, for every iteration, a new call will be made
		instead what we do is that we allocate memory first and then "place"
		the constructed object in that place
		*/

		char* buffer = new char[sizeof(T)*n];
		T* array = reinterpret_cast<T*>(buffer);
		for (int i = 0; i < n; i++)
		{
			new(array + i) T{};
		}
		m_array = array;
	}

	CArray(const CArray& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		char* buffer = new char[sizeof(T)*m_capacity];
		T* array = reinterpret_cast<T*>(buffer);
		for (int i = 0; i < m_size; i++)
		{
			new(array + i) (*(other.m_array + i));
		}
		m_array = array;
	}

	void Shrink(int shrinkBy)
	{
		if (m_capacity - shrinkBy < m_size)
		{
			std::cout << "Can't shrink with " << shrinkBy << ". Max possible is " << m_capacity - m_size << ".\n";
			return;
		}

		int newCapacity = m_capacity - shrinkBy;
		ChangeCapacity(newCapacity);
	}

	void Expand(int expandBy)
	{
		int newCapacity = m_capacity + expandBy;
		ChangeCapacity(newCapacity);
	}

	int Size() const
	{
		return m_size;
	}

	void Clear()
	{
		for (int i = 0; i < m_size; ++i)
		{
			T* current = m_array + i;
			current->~T();
		}
		char *buff = reinterpret_cast<char*>(m_array);
		delete[] buff;
		m_size = 0;
		m_capacity = 0;
		m_array = nullptr;
	}

	bool Empty() const
	{
		return m_size == 0;
	}

	T& operator[](int index) const
	{
		return (m_array + index);
	}

	int Capacity() const
	{
		return m_capacity;
	}


};