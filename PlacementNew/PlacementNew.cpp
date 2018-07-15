// PlacementNew.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Array.h"

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

};
std::string CDebugString::count{ "Obj0" };

int main()
{
	CArray<CDebugString> array(1);
	array.Expand(1);
    return 0;
}

