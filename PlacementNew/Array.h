#pragma once
template<typename T>
class CArray
{
	T* m_array{ nullptr };
	int m_size{};
	int m_capacity{};
	
	void CopyOverAndDestructDescending(T* oldArray, int oldSize, T* newArray)
	{
		/*
		old: A A A _ _ _
		new: _ A A A _ _
		*/
		for (int i = oldSize - 1; i >=0 ; --i)
		{
			new(newArray + i) T{ (*(oldArray + i)) };
			(oldArray + i)->~T();
		}
	}

	void CopyOverAndDestruct(T* oldArray, int oldSize, T* newArray)
	{
		for (int i = 0; i < oldSize; ++i)
		{
			new(newArray + i) T{ (*(oldArray + i)) };
			(oldArray + i)->~T();
		}
		
	}

	void ChangeCapacity(int newCapacity)
	{
		if (newCapacity < m_size)
		{
			std::cout << "Can't change the capacity to " << newCapacity << ", since it is less than size " << m_size << ".\n";
		}

		char* newBuffer = new char[sizeof(T)*newCapacity];
		T* newArray = reinterpret_cast<T*>(newBuffer);
		CopyOverAndDestruct(m_array, m_size, newArray);
		
		char* oldBuffer = reinterpret_cast<char*>(m_array);
		delete[] oldBuffer;
		
		m_array = newArray;
		m_capacity = newCapacity;
	}

	void EnsureExtraCapacity()
	{
		if (m_size < m_capacity)
		{
			return;
		}

		int newCapacity = m_capacity * 2;
		ChangeCapacity(newCapacity);
	}

public:
	CArray()
	{

	}

	CArray(int n)
	{
		char* buffer = new char[sizeof(T)*n];
		T* array = reinterpret_cast<T*>(buffer);
		for (int i = 0; i < n; i++)
		{
			new(array + i) T{};
		}
		m_array = array;
		m_size = n;
		m_capacity = n;
	}

	CArray(const CArray& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		char* buffer = new char[sizeof(T)*m_capacity];
		T* array = reinterpret_cast<T*>(buffer);
		for (int i = 0; i < m_size; i++)
		{
			new(array + i) T(*(other.m_array + i));
		}
		m_array = array;
	}
	void AddBack(const T& element)
	{
		Insert(m_size - 1, element);
	}

	void AddFront(const T& element)
	{
		Insert(0, element);
	}

	void Insert(int index, const T& element)
	{
		EnsureExtraCapacity();
		CopyOverAndDestructDescending(m_array+index, m_size - index, (m_array + index + 1);
		new(m_array + index) T{ element };
		m_size++;
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