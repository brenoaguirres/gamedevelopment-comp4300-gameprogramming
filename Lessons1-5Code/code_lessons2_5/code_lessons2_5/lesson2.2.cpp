#include<iostream>
#include<vector>
#include<fstream>

class Student
{
	std::string m_firstname = "first";
	std::string m_lastname  = "last";
	int			m_id	    = 0;
	float		m_average   = 0;
public:
	Student() {}

	Student(std::string first, std::string last, int id, float avg)
		: m_firstname(first)
		, m_lastname(last)
		, m_id(id)
		, m_average(avg)
	{

	}

	~Student()
	{

	}

	// methods
	int getAvg() const // preserves return value
	{
		return m_average;
	}

	int getID() const
	{
		return m_id;
	}

	std::string getLastName() const
	{
		return m_lastname;
	}

	std::string getFirstName() const
	{
		return m_firstname;
	}

	void print() const
	{
		std::cout << m_firstname << " " << m_lastname << " " << std::endl;
		std::cout << m_id << " " << m_average << " " << std::endl;
	}

	void doMachineLearning(std::string& s) const // pass reference when handling large data to avoid copy
	{
		std::cout << s << std::endl;
	}
};

class Course
{
	std::string m_name = "Course";
	std::vector<Student> m_students;
public:
	Course() {}

	Course(const std::string& name)
		: m_name(name)
	{

	}

	void addStudent(const Student& s)
	{
		m_students.push_back(s);
	}

	const std::vector<Student>& getStudents() const // return value cant be changed, function wont change anything
	{
		return m_students;
	}

	void print() const
	{
		for (const auto& s : m_students)
		{
			s.print();
		}
	}
};

int test_class()
{
	Student s1;
	Student s2("Dave", "Churchill", 1, 3.14f);
	const Student s3("Jane", "Doe", 202200001, 99.9); // const

	s3.print();

	// const correctness - mark every non changing function as const

	Course comp4300("COMP 4300");
	comp4300.addStudent(s1);
	comp4300.addStudent(s2);
	comp4300.addStudent(s3);
	comp4300.addStudent(Student("Billy", "Bob", 3, 50.0f));
	comp4300.print();

	return 0;
}

void loadFromFile()
{
	std::ifstream fin("config.txt");
	std::string first, last;
	int id;
	float avg;

	while (fin >> first)
	{
		fin >> last >> id >> avg;
		addStudent(Student(first, last, id, avg));
	}
}

int test_read()
{
	loadFromFile();
}	