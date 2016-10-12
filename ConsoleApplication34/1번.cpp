#include<iostream>
#include<string>
template<typename T>

void print(const T& i)
{
	std::cout << i << std::endl;
}
int main()
{
	print(1);
	print(1.1f);
	print("iostream!");
}