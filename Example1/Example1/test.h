#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <future>
using namespace std;

class Foo
{
public:

	// constructor
	Foo() : _name{ "" }, _age{ 0 }
	{

	}

	~Foo()
	{
		cout << *this << " is destroyed.\n";
	}

	// constructor
	Foo(string name, int age) : _name{ name }, _age{ age }
	{

	}

	void setAge(int age) {
		this->_age = age;
	}

	friend ostream& operator<<(ostream& os, const Foo& foo)
	{
		os << "name:" << foo._name << " age:" << foo._age << "\n";
		return os;
	}

	// copy constructor
	Foo(const Foo& foo) : _name{foo._name},_age{foo._age}
	{
		std::cout << "Foo copy constructor\n";
	}

	// copy assignment
	Foo& operator=(Foo& other)
	{
		if (this != &other)
		{
			std::cout << "Foo copy assignment\n";
			_name = { other._name };
			_age = { other._age };
		}

		return *this;
	}

	// move constructor
	Foo(Foo&& foo) : _name{ std::exchange(foo._name,"") },_age{std::exchange(foo._age,0)}
	{
		std::cout << "Foo move constructor\n";
	}

	Foo& operator=(Foo&& other)
	{
		if (this != &other)
		{
			std::cout << "Foo move assignment\n";
			_name = std::exchange(other._name, ""); // _name = other._name;
			_age = std::exchange(other._age, 0);   // _age = other._age;
		}

		return *this;
	}

	string getname() const
	{
		return _name;
	}
private:
	string _name;
	int _age;
};


Foo create_local_foo(void)
{
	Foo foo("Peter", 41);

	return foo;
}

void text_exchange()
{
	vector<int> v;

	std::exchange(v, { 1,2,3,4 });

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
	//std::cout << "\n\n";
}


std::unique_ptr<Foo> test_unique_ptr(std::unique_ptr<Foo> foo)
{
	std::cout << foo->getname();

	return foo;
}

void test_unique_ptr2(Foo& foo)
{
	std::cout << foo.getname();
	foo.setAge(50);

}


struct F
{
	vector<double>& vec;
	F(vector<double>& vv) : vec{ vv }
	{
		cout << "F struct constr\n";
	}

	double operator()()
	{
		double sum = 0;
		for_each(vec.begin(), vec.end(), [&](double a) {sum += a; });
		return sum;
	}
};

double f(const vector<double>& v)
{
	double sum = 0;
	for_each(v.begin(), v.end(), [&](double a) {sum += a; });
	return sum;
}

namespace test
{
	template <class Iterator, class U = typename std::iterator_traits<Iterator>::value_type>
	U sum(Iterator first, Iterator last)
	{
		U sum = U{};
		for (auto it = first; it != last; ++it) {
			sum += *it;
		}
		return sum;
	}

	template <class Iterator>
	typename std::iterator_traits<Iterator>::value_type sum2(Iterator first, Iterator last)
	{
		using U = typename std::iterator_traits<Iterator>::value_type;
		U sum = U{};
		for (auto it = first; it != last; ++it) {
			sum += *it;
		}
		return sum;
	}

	template<typename Cont, typename Pred>
	auto find_if(Cont& cont, Pred p) 
	{
		return std::find_if(begin(cont), end(cont), p);
	}
}

template<typename type>
class Parent
{
public:
	type value;


	typedef typename type value_type;
	value_type second;
};

template<typename T>
class Child : public Parent<float>
{
public:
	typedef typename Parent<int> _myBase;

	std::vector<T>  vec;
	typedef typename std::vector<T>::const_iterator iter_t;
	iter_t * p2; // iter_t is a dependent name, but it's known to be a type name

	
};





bool LookPattern(double d)
{
	return d == 500;
}

void code(vector<double>& v1, vector<double>& v2)
{
	Child<double> child;
	
	Child<double>::iter_t t;
	//std::vector<int>::iterator
	
	auto ret = test::find_if(v1, LookPattern) != cend(v1);
	std::vector<double> aaa{ 1,2,3 };
	auto sumRes = test::sum(aaa.begin(), aaa.end());
	F ff = F{ v2 };

	auto ss = ff();
	std::thread t1{ f,v1 };
	std::thread t2{ F{ v2 } };
	double sum = 0;
	std::thread t3{ [&]() {sum = f(v2); } };

	auto res1 = async(f, v2);
	auto res2 = async(F{ v2 });


	t1.join();
	t2.join();
	t3.join();

	cout << "asyn1 =" << res1.get() << " asyn2 =" << res2.get() << "\n";
}


