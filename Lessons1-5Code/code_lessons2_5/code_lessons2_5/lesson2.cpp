#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include "lessons_headers.h"

using namespace nmsp;
using namespace std;

class Point
{
	int m_x = 0;
	int m_y = 0;
public:
	Point(int x, int y)
		: m_x(x)
		, m_y(y)
	{
		std::cout << "Class constructed" << std::endl;
	}

	~Point()
	{
		std::cout << "Class deconstructed" << std::endl;
	}
};

int main(int argc, char* argv[])
{
	// First cpp
	std::cout << "Hello World!" << std::endl;
	
	// Whitespaces 1
	/*
	*  Whitespaces 2
	*/

	// indent / braces
	int test = 0;
	if (test == 0)
	{
		std::cout << "test equals 0" << std::endl;
	}

	nmsp::test(10);

	// STL Containers
	std::vector<int> vec;
	//std::vector<int> vec(0, 1);
	//std::cout << vec[0] << std::endl;
	vec.push_back(2);
	vec.pop_back();
	vec.clear();
	vec.reserve(3);
	vec[0] = 5;
	vec[1] = 2;
	vec[2] = 10;

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << std::endl;
	}

	for (auto i : vec)
	{
		std::cout << vec[i] << std::endl;
	}

	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}
	
	for (auto & i : vec)
	{
		std::cout << i << std::endl;
	}

	std::set<int> st;
	st.insert(0);
	st.find(0);
	st.erase(0);

	for (auto & i : st)
	{
		std::cout << i << std::endl;
	}

	std::map<std::string, int> m;
	m["Dave"] = 25;
	m["Mom"] = 50;
	for (auto kv : m)
	{
		std::string name = kv.first;
		int age = kv.second;
	}

	

	return 0;
}