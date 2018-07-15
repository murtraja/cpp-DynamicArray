#pragma once
template<typename T>
class CArray
{
	T* m_array{ nullptr };
	int m_size{};
	int m_capacity{};
	
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
};