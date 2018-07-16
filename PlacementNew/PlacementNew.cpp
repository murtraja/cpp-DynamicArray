// PlacementNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Array.h"
#include <assert.h>

#define _USE_ASSERT
#ifdef _USE_ASSERT
#define MASSERT(x,y) assert(x && y)
#else
#define MASSERT
#endif // _USE_ASSERT

class CDebugString
{
	std::string m_string;

	void UpdateCount()
	{
		for (std::size_t i = 0; i < count.length(); ++i)
		{
			if (isdigit(count[i]))
			{
				std::string prefix = count.substr(0, i);
				std::string currentNum = count.substr(i);
				int no = stoi(currentNum);
				no++;
				std::string newCount{ std::to_string(no) };
				count = prefix + newCount;
				break;
			}
		}
	}
public:
	static std::string count;
	CDebugString()
		: m_string(count)
	{
		UpdateCount();
	}
	CDebugString(const char* str)
		: m_string(str)
	{

	}

	static std::function<void(const CDebugString&)> GetPrinter()
	{
		return [](const CDebugString& element)
		{
			std::cout << element.m_string << " ";
		};
	}

	bool operator==(CDebugString& other) const
	{
		return m_string == other.m_string;
	}

};
std::string CDebugString::count{ "Obj1" };

void Test1()
{
	CArray<CDebugString> array{};
	array.AddBack(CDebugString{});
	array.AddBack(CDebugString{});
	array.AddBack(CDebugString{});
	array.AddBack(CDebugString{});
	array.AddFront(CDebugString{"ObjFront"});
	array.Insert(3, CDebugString{"ObjInserted"});
	array.PrintAll(CDebugString::GetPrinter());
	
	auto copiedArray(array);
	copiedArray.PrintAll(CDebugString::GetPrinter());
}

void Test2()
{
	CArray<CDebugString> array{};
	CDebugString s1{};
	CDebugString _s1{ "Obj1" };
	array.AddBack(s1);
	array.AddBack(CDebugString{});
	array.AddBack(_s1);
	int foundIndex = array.Find(_s1);
	MASSERT(foundIndex == 0, "Find returned an invalid index.");

	array.Remove(s1);
	array.Remove(s1);

	array.PrintAll(CDebugString::GetPrinter());
}

int main()
{
	Test2(); 	
    return 0;
}

