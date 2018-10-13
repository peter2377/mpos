// Example1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <cctype>
#include <numeric>
#include <memory>  // for unique_ptr
#include "test.h"
#include <algorithm>

using namespace std;





//covarianz


class Base
{
public:
	virtual Base* getThis() { return this; }
	void printType()
	{
		cout << "This is called from Base\n";
	}
};


class Derived : public Base
{
public:
	virtual Derived* getThis() override { return this; }

	void printType()
	{
		cout << "This is called from Derived\n";
	}
};



class Address
{
public:
	size_t _id;
	string _street;

	Address(size_t id, const string& street) : _id(id), _street(street)
	{

	}
};

void testCovarianz()
{
	Derived d;
	d.getThis()->printType();
	Derived* b = &d;
	b->getThis()->printType();

	int sh = -20;
	unsigned int ui = 200;
	
	if ( sh < (int)ui)
	{
		cout << "i'm in the if loop \n";
	}
}

class Person
{
public:
	size_t _id;
	string _name;
	string _phone;

	Address *_address;



	Person(size_t id, const string& name, const string &phone) : _id(id), _name(name), _phone(phone)
	{

	}

	void SetAddress(Address* address)
	{
		_address = address;
	}

	friend ostream& operator<<(ostream &os,const Person &person)
	{
		assert(person._address != nullptr && "Try again.....");
		
		os << "Id: " << person._id << " Name: " << person._name << " Phone: " << person._phone << " Street: " << person._address->_street<<std::endl;

		return os;
 	}
};





/*template<typename T>
struct reversed_mapper {
	const &T _v;

	reversed_mapper(const T& v) : _v(v) {}

	auto begin() -> decltype(rbegin(_v))
	{
		return rbegin(_v);
	}

	auto end() -> decltype(rend(_v))
	{
		return rend(_v);
	}
};

template<typename T>
reversed_mapper<T> reversed(const T& v)
{
	return reversed_mapper<T>(v);
}*/

void test_array(std::array<uint8_t,64>* array)
{
	cout << "Size= " << array->size() << "Sizeof= " << sizeof(array) <<endl;
}


//void printElements(int(&arr)[4])
  //void printElements(int* arr)
void printElements(int (&arr)[5])
{
	int length{ sizeof(arr) / sizeof(arr[0]) }; // we can now do this since the array won't decay

	for (int i{ 0 }; i < length; ++i)
	{
		std::cout << arr[i] << std::endl;
	}
}


void SearchName(const vector<std::string>& names)
{
	cout << "Enter a name to search:";
	string nameToSearch;
	cin >> nameToSearch;
	auto bFound(false);
	for (const auto &name : names)
	{
		if (name.compare(nameToSearch) == 0)
		{
			bFound = true;
			break;
		}
	}
	std::array<int, 5> myArray = { 9, 7, 5, 3, 1 }; // initialization list
	std::array<int, 5> myArray2{ 9, 7, 5, 3, 1 }; // uniform initialization
	if (bFound) cout << "Name: " << nameToSearch << " was found." << std::endl;
	else cout << "Name: " << nameToSearch << " was not found." << std::endl;
}



void bitsetFnc()
{
	constexpr int max = 8;
	//bitset<max> b;
	int i;

	int a = 8;

	int aInv = ~a + 1;

	//while (cin >> b)
	while ((std::cin >> i)) 
	{
		
		//cin >> b;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	
		cout << std::dec << i <<"==" << std::hex << "0x" << i << "=="<<bitset<2*sizeof(int)>(i) << endl;
		/*for (size_t i = 0; i < max; i++)
		{
			cout << b[i];
			cout << endl;
		}*/

		
	}
}

void assignObjects(const std::vector<Person*> & persons, const std::vector<Address*> & address)
{
	auto itPerson = persons.begin();
	auto itAddress = address.begin();

	for (;itPerson != persons.end();itPerson++)
	{
		for (itAddress = address.begin(); itAddress != address.end(); itAddress++)
		{
			if ((*itPerson)->_id == (*itAddress)->_id)
			{
				(*itPerson)->SetAddress((*itAddress));
			}
		}
	}
}
//std::vector<int> bigVector(1024 * 1024  * 1);

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

static inline void ltrim(string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
	{
		return !std::isspace(ch);
	}));
}

static inline void rtrim(string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
	{
		return !std::isspace(ch);
	}).base(),s.end());
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	/* 1.) reove all spaces */
	string sss = s;
//	ltrim(sss);
	std::string::iterator end_pos = std::remove_if(sss.begin(), sss.end(), isspace);
	sss.erase(end_pos, sss.end());
	// oder
	sss = s;
	//sss.erase(std::remove(sss.begin(), sss.end(), ' '), sss.end());
	end_pos = std::remove(sss.begin(), sss.end(), ' ');
    sss.erase(end_pos, sss.end());

	/* 2.) removel multiple spces*/
	bool prev(false);
	string str = s;
	char rem(' ');
	auto iter = std::remove_if(str.begin(), str.end(), [&](char c) -> bool {
		if (c == rem && prev) {
			return true;
		}
		prev = (c == rem);
		return false;
	});
	str.erase(iter, str.end());

	str = s;
	
	/* 3.) removel multiple spces*/
	std::string::iterator new_end =
		std::unique(str.begin(), str.end(),
			[=](char lhs, char rhs) -> bool { return (lhs == rhs) && (lhs == ' '); }
	);
	str.erase(new_end, str.end());

	/* 4.) removel multiple spces*/
	new_end = std::unique(str.begin(), str.end(), BothAreSpaces);
	str.erase(new_end, str.end());


	/* remove if char is is digit or alphanumeric 
	new_end = std::remove_if(str.begin(), str.end(), [&](char ch) -> int { return !isalnum(ch); });
	str.erase(new_end, str.end());
	*/
	/* split string in words */
	ltrim(str);
	rtrim(str);
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

static void fillvector(std::vector<int>& v)
{
	iota(v.begin(), v.end(), 20);

	std::copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}
template<class ForwardIterator,class T>
void iota_n(ForwardIterator first, int n, T value)
{
	for (size_t i = 0; i < n; i++)
		*first++ = value++;
	
}

template<class InputIt,class OutputIt>
void mycopy(InputIt first, InputIt last, OutputIt d_first)
{
	while (first != last)
	{
		*d_first++ = *first++;
	}
}

template<class InputIterator, class T>
void myfill_n(InputIterator first, InputIterator last, T value)
{
	while (first != last)
		*first++ = value;
}

namespace myswap
{ 
	template<class T>
	void swap(T& a, T& b)
	{
		T tmp;
		tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);

	}
}


template<typename I>
auto slide(I f, I l, I p) -> pair<I, I>
{
	//if (p < l) return{ p,std::rotate(p,f,l) };
	if (l < p) return{ std::rotate(f,l,p),p };
}

template<typename BidirIterator, typename Predicate>
auto gather(BidirIterator first, BidirIterator last,
	BidirIterator position, Predicate p) -> std::pair<BidirIterator, BidirIterator>
{
	return{ std::stable_partition(first, position, std::not1(p)),
		    std::stable_partition(position, last, p) };
}

struct Kind;
struct Eltern
{
	~Eltern() { cout << "Bye eltern\n"; }

	shared_ptr<Kind> kind;
	void sayHello()
	{
		cout << "Eltern says Hello\n";
	}
};


struct Kind
{
	~Kind() { cout << "Bye Kind\n"; }

	weak_ptr<Eltern> eltern;
};


shared_ptr<Eltern> createEltern()
{
	auto elt = make_shared<Eltern>();
	elt->sayHello();

	return elt;
} 


// explicit_specialization.cpp  
template<class T> void func(T t)
{
	cout << "f commom\n";
}

// Explicit specialization of f with 'char' with the  
// template argument explicitly specified:  
//  
template<> void func<char>(char c)
{
	cout << "char spec.\n";
}

// Explicit specialization of f with 'double' with the  
// template argument deduced:  
//  
template<> void func(double d)
{
	cout << "double spec. \n";
}



template<typename T,typename U>
auto addvalue(T&& a,U&& b) -> decltype (forward<T>(a) + forward<U>(b))
{
	cout << "addition commom\n";
	return forward<T>(a) +forward<U>( b);
}


//template<>
//auto addvalue(string&& a,string&& b) 
//{
//	cout << "addition specialized\n";
//	return forward<string>(a) + forward<string>(b);
//}


template<typename T1, typename T2>
auto Plus(T1&& t1, T2&& t2) ->
decltype(forward<T1>(t1) + forward<T2>(t2))
{
	std::is_class
	return forward<T1>(t1) + forward<T2>(t2);
}

template<class _Ty>
struct is_classy
	: _Cat_base<__is_class(_Ty)>
{	// determine whether _Ty is a class
};


template<class _Ty1,
	class _Ty2,
class _Ty3>
	struct is_samex
	
{	
	// determine whether _Ty1 and _Ty2 are the same type 
	//is_samex(){}

	//is_samex(_Ty1 a,_Ty2 b) {}
	string s = "struct _1\n";
	_Ty1 type1;
	_Ty2 type2;
};

template<class _Ty1,class _Ty2>
struct is_samex<_Ty1, _Ty1,_Ty2>

{	// determine whether _Ty1 and _Ty2 are the same type
	string s1 = "struct _1\n";
};

template<class _Ty1>
struct is_samex<_Ty1,_Ty1,_Ty1>
	
{	// determine whether _Ty1 and _Ty2 are the same type
	string s2 = "struct _2\n";
};


template<class _Ty1, class _Ty2>
struct is_samex<bool, _Ty1, _Ty2>

{	// determine whether _Ty1 and _Ty2 are the same type
	string s3 = "struct _3\n";
};

template<bool,typename A =void>
struct SayHello
{
	void sayNothing()
	{

	}


};

template<typename A>
struct SayHello<true,A>
{
	void sayHello()
	{

	}

	typedef A type;
};

int accumulate_worker(std::vector<int>& v)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return accumulate(v.begin(), v.end(), 0);
}

using int_futres = std::vector<std::future<int>>;

//int_futures launch_split:worker_async()

int main()
{

	std::vector<int> vecacc(10);
	std::iota(vecacc.begin(), vecacc.end(), 1);
	int* array1 = &vecacc[0];
	int* array2 = &vecacc[vecacc.size() / 2];

	std::vector<int> vec333{ vecacc.begin(),vecacc.begin() + 3 };

	size_t midlle = vecacc.size() / 2;
	std::vector<int>::iterator middleIter(vecacc.begin());
	std::advance(middleIter, midlle);
	std::vector<int> vec111(vecacc.begin(), middleIter);
	std::vector<int> vec2222(middleIter,vecacc.end());
	
	std::future<int> fut = std::async(std::launch::async, accumulate_worker, vecacc);


	while (fut.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
	{
		cout << " ...still not ready\n";
	}
	std::cout << "get_res: " << fut.get();
	SayHello <bool{ true }, string > xy;
	is_samex<bool, char,bool> test1;
	//is_samex<int, char> b;
	char t;
	func((double)10.0L);
	func('a');
	func("sttr");
	int x = 10, y = 10;
	auto bbbb = std::is_same<int,int>::value;
	auto addition = addvalue(x, y);
	auto addition2 = addvalue(string("xxx"), string("yyy"));
	bool_constant<true> boolcon;
		
	cout << std::boolalpha << std::true_type::value<< "   " << boolcon.value;
	createEltern();
	//if (newEltern.expired())
		cout << "newEltern expired\n";

	{
			auto uniq = std::make_unique<Eltern>();
		auto kind = make_shared<Kind>();
		auto eltern = make_shared<Eltern>();
		eltern->kind = kind;
		kind->eltern = eltern;

		//eltern->kind = nullptr;
	}
	Child<string>::_myBase iiii;

	iiii.value = 10;
	Parent<int>::value_type i = 10;

	int myints[] = { 10,200,29,40,50,52,70,90 };

	std::vector<int> vec(myints, myints + 8);
	std::sort(vec.begin(), vec.end());
	
	// rotate

	std::vector<int> rot(10);
	std::iota(rot.begin(), rot.end(), 1);

	auto low = std::lower_bound(vec.begin(), vec.end(), 51);
	auto upper = std::upper_bound(vec.begin(), vec.end(), 50);
	std::cout << "lower_bound at position " << (low - vec.begin()) << '\n';
	std::cout << "upper_bound at position " << (upper - vec.begin()) << '\n';


	rotate(rot.begin()+3, rot.begin() + 4, rot.begin()+5);

	auto findidx = std::find_if(rot.begin(), rot.end(), [](int val) { return val == 3; });
	auto it0 = rot.begin();
	 std::next(it0, 5);
	auto dist = std::next(rot.begin(), std::distance(rot.begin(), rot.end()) / 2);
	auto dist2 = *std::next(rot.begin(), std::distance(rot.begin(), rot.end()) / 2);

	//auto xxx = std::next(rot.begin(), 5);
	//auto xx = rot.begin() + 5;
	

	std::vector<int>::size_type len_rot = std::distance(rot.begin(), rot.end()) / 2;
	
	auto f = rot.begin();
	auto l = rot.begin() + 3;
	auto p = rot.end() - 3;

	//auto ret = slide(f, f+5, rot.end());

	auto ret = slide(f, l, p);


	
	ret = slide(f, p-3,p);

	
	//ret = slide(f+1, rot.end()-3, rot.end()-2);
	

	rot[2] = rot[2] * 11;
	rot[8] = rot[8] * 11;
	rot[5] = rot[5] * 11;
	rot[6] = rot[6] * 11;
	
	std::function<bool(int)> modulo11 = [](int value) { return (value % 11 == 0); };
	auto gat = gather(rot.begin(), rot.end(), rot.begin()+5, modulo11);

	auto part_location1 = std::stable_partition(rot.begin(), rot.end(), std::not1(modulo11));
	auto part_location2 = std::stable_partition(rot.begin(), rot.end(), (modulo11));
	
//	std::copy(rot.begin(), rot.end(), std::ostream_iterator<int>(cout, " "));

	
	vector<double> vec1(100);
	vector<double> vec2(100);

	//std::iota(vec1.begin(), vec1.end(), 0);
	std::generate(vec1.begin(), vec1.end(), [n = 1]() mutable {return n++; });
	std::generate(vec2.begin(), vec2.end(), [n = 1]() mutable {return n++; });

	code(vec1, vec2);
	using strIterator = std::string::iterator;

	strIterator strIter;
	string peter = "peter";
	string copy = std::exchange(peter, "karl");

	Foo fooinstance1 = create_local_foo();
	Foo fooinstance2;
	fooinstance2 = fooinstance1;
	const Foo fooinstance3 = fooinstance1;
	fooinstance3.getname();
	text_exchange();

	
		auto make_ptr = std::make_unique<Foo>("Jani", 13);
	make_ptr = test_unique_ptr(std::move(make_ptr));
	test_unique_ptr2(*(make_ptr.get()));
//		cout << *make_ptr;
	
	int sw1 = 10, sw2 = 20;
	myswap::swap(sw1, sw2);
	std::swap(sw1, sw2);

	string name = "Peter";
	//name.resize(name.length() - 1);
	cout << "size: " << name.size() << "cap: " << name.capacity() << name << " \n";
	auto iterator = std::remove(name.begin(), name.end(), 'r');
	cout << "size: " << name.size() << "cap: " << name.capacity() << name << " \n";
	name.erase(iterator, name.end());
	cout << "size: " << name.size() << "cap: " << name.capacity() << name << " \n";

	testCovarianz();
	vector<int> v(10);
	myfill_n(v.begin(), v.end(), 300);
	iota_n(back_inserter(v),5, 10);
	//iota_n(v.begin(), 100, back_inserter(v));
	vector<int> v2;
	iota(v.begin(), v.end(), 0);
	mycopy(v.begin(), v.end(), back_inserter(v2));



	std::fill_n(back_inserter(v), 5, -1);

	fillvector(v);

	split("        Peter Steinhaus  jani  jona      ", ' ');
	
	Address addr1 = { 1,"Pappelallee" };
	Address addr2 = { 2,"D4,1" };
	std::vector<Address*> address = { &addr1,&addr2 };
	Person person1 = { 20,"Peter","4318086" };
	Person person2 = { 1,"Jani","4218086" };
	Address addr3 = { 3,"Hessische STrasse" };

	static_assert(sizeof(double) == 8, "long is not 4 bytes");
	
	std::vector<Person*> persons = { &person1,&person2 };

	assignObjects(persons, address);
	
	for (const auto& p : persons)
		cout << *p;

	address.insert(address.begin(), &addr3);
	person1._id = 30;
	assignObjects(persons, address);

	for (const auto& p : persons)
		cout << *p;

	int value = 10;
	int value2 = 1000;
	 const int * zeiger = &value;
	zeiger = &value2;

	long double fixedarray[] = { 1,2,3,4,5 };
	cout << "sizeof(fixedarray)= " << sizeof(fixedarray) << std::endl;
	cout << "sizeof(fixedarray)= " << sizeof(fixedarray) / sizeof(fixedarray[0]) << std::endl;
	//std::vector<bool> bools{ true,false,false,true,true };
	std::vector<int> bools{ 1,2,3,4,5,6,3,6 ,2,6,3,3,3,3,3,3,3,3};
	//bools.resize(100);
	int size = sizeof(int) * bools.size();
	int len = sizeof(bools)+size;
	int len1 = sizeof(bools[0]);
	size_t aaaaa = sizeof(bools);
	size_t lenTyp = sizeof(bools) + sizeof(int) *bools.capacity();
	cout << "sizeof(bools)= " << len << std::endl;
	cout << "sizeof(bools)= " << size/len1 << std::endl;
	for (const auto &element : bools)
		std::cout << element << " ";

	std::vector<string> names = { "Peter","Jani","Jona" };

	string* pString = &names[1];
	cout << *pString;

	names.resize(100);
	cout << *pString;
	const std::vector<string>::iterator it = names.begin();

	names.insert(it+1,"Steinhaus");
	cout << *pString;
	SearchName(names);
	std::bitset<16> foo;

	std::cout << "Please, enter a binary number: ";
	std::cin >> foo;

	if (foo.any())
		std::cout << foo << " has " << foo.count() << " bits set.\n";
	else
		std::cout << foo << " has no bits set.\n";


	int testarray[] = { 1,2,3,4,5,6,7 };

	auto bFirst = true;
	for (auto var : testarray)
	{
		if (bFirst) bFirst = false;
		else
			cout << ",";
		var += 10;
		std::cout << var;
	}
	cout << std::endl;




	//bitsetFnc();
	int arr[]{ 99, 20, 14, 80,120 };

	printElements(arr);

	constexpr int val = 2521;
	for (auto i = 1; i <= 10; i++)
		cout << val << "/" << i << "=" << val % i << endl;
	


	const long  kBaudrates[] = { 50, 75, 110,10,255,244 };
	auto aaa = sizeof(kBaudrates);
	auto var = std::size(kBaudrates);//sizeof(kBaudrates) / sizeof(kBaudrates[0]);
	
	for (int i = sizeof(kBaudrates) / sizeof(char*); --i >= 0;)
	{
		cout << kBaudrates[i];
	}
	
	
	cout << "UINT_MAX:" << sizeof(size_t) << "npos:" << string::npos << endl;
	int a = 100;
	int b = 30;

	
	printf("_MSC_VER : %d \n", _MSC_VER);
	printf("_MSC_FULL_VER : %d \n", _MSC_FULL_VER);
	printf("_MSC_BUILD : %d \n", _MSC_BUILD);

#ifdef _MSVC_LANG
	printf("_MSVC_LANG : C++%x \n", (_MSVC_LANG));
	printf("_MSVC_LANG : C++%d \n", (_MSVC_LANG / 100));
	printf("_MSVC_LANG : C++%d \n", (_MSVC_LANG / 100) % 2000);
#endif

	
	string str;
	getline(cin, str);
    return 0;
}

