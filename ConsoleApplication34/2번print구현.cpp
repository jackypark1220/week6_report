#include<iostream>
#include<string>
#include<vector>
template<typename T>
class Vector2D
{
public:

	T x, y;
	Vector2D(const T& x_, const T& y_)
		:x(x_), y(y_) {}
	void print()
	{
		std::cout << x << " " << y << std::endl;
	}

};


int main()
{

	Vector2D<int> int_vector(1, 1);
	int_vector.print();

}