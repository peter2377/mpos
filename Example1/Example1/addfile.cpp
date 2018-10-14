#include <iostream>
#include <vector>


using namespace std;

using myint = int;


class Shape
{
	public:
	Shape(int a) : x{a}
		{
		}
		virtual ~Shape()
		{
		}
		
		private:
		int x;
	
}