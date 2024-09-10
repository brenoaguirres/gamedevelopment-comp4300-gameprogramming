#include <iostream>
#include <memory>

// pass by value resource
void tennify(int a) { a = 10; }

// pass by pointer resource
void tennify(int* a) { *a = 10; }

// pass by reference resource
void tennify(int& a) { a = 10; }

// RAII resource
class IntArray
{
	int* array;
public:
	IntArray(size_t size) { array = new int[size]; } // constructor ACQUIRE resource
	~IntArray() { delete[] array; } // destructor RELEASE resource
	int& operator [] (size_t i) { return array[i]; }
};

// shared pointers resource
class Point
{
	float m_x;
	float m_y;
public:
	Point() {}
	~Point() {}
	void print() const
	{
		std::cout << "(" << m_x << "," << m_y << ")" << std::endl;
	}
};

void func(std::shared_ptr<Point> pt)
{
	pt->print();
}

// variable examples
void pp(int& i)
{
	std::cout << &i << " " << i << " " << sizeof(i) << std::endl;
}

// templating classes
template <class T>
	class DynamicArray
	{
		size_t m_size;
		T* m_arr;
	public:
		DynamicArray(size_t size)
			: m_size(size)
			, m_arr(new T[m_size])
		{
			std::cout << "Array Constructor" << std::endl;
		}

		~DynamicArray()
		{
			delete[] m_arr;
			std::cout << "Array Destructor" << std::endl;
		}

		T get(size_t index) const
		{
			return m_arr[index];
		}

		void set(size_t index, T val)
		{
			m_arr[index] = val;
		}

		void print() const
		{
			for (size_t i = 0; i < m_size; i++)
			{
				std::cout << i << " " << m_arr[i] << std::endl;
			}
		}

		// operator overloads
		const T& operator [] (size_t index) const
		{
			return m_arr[index];
		}

		T& operator (size_t index)
		{
			return m_arr[index];
		}
	};

// main class
void lesson3()
{
	// mem allocation
	int val = 5; // stack
	int* hval = new int; // heap
	*hval = 5;

	// array alloc
	int a[5]; // stack
	int* ha = new int[5]; // heap
	ha[3] = 10;

	// pointers
	int va = 6; // variable decl
	int* po;	// pointer decl
	po = &va;	// recv address of va
	*po = 7;	// dereference va

	// array pointers
	int* arr = new int[3];
	arr[0] = 5;
	arr[1] = 10;
	*(arr + 2) = 20; // index 2
	// arr[n] == *(arr+n)
	// n[arr] == *(n+arr)
	// (arr+n) == &(arr[n])

	// pass by value
	int i = 12;
	tennify(12); //PBV - copy
	std::cout << i << std::endl; // will print 12

	// pass by pointer
	i = 12;
	tennify(&i); // PBR via pointer - pointer may be null
	std::cout << i << std::endl; // will print 10

	// pass by reference
	i = 12;
	tennify(&i); // PBR via reference - passing the reference, so it'll handle null values and type issues
	std::cout << i << std::endl;

	// C++ RAII
	IntArray arr(10); // mem allocated
	arr[5] = 21; // at end of program destructor dealloc mem - we dont need to care with alloc / dealloc

	// shared pointers -> include RAII
	auto sp = std::make_shared<Point>();
	func(sp);

	// variable examples
	int poa = 10;
	int pob = 25;

	pp(poa);
	pp(pob);

	// array examples
	int ae_arr[10] = {}; // default array inititalization
	int* ae_harr = new int[10];

	for (size_t i = 0; i < 10; i++)
	{
		pp(ae_arr[i]);
	}

	for (size_t i = 0; i < 10; i++)
	{
		pp(ae_harr[i]);
	}

	// pointer examples
	int p_a = 10;
	int p_b = 25;
	int* pp_a = &p_a;
	int* pp_b = &p_b;

	*pp_a = 17; 
	*(&p_a) = 20; // same as previous line

	*pp_b = 17;
	*(pp_b - 1) = 10; // accessing p_a address via pp_b, very UNSAFE

	pp(p_a);
	pp(p_b);

	// Templating classes
	DynamicArray<int> myArray(10);
	myArray.set(4, 7);
	myArray.set(2, 137);
	myArray.print();
}
