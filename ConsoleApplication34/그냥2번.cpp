#include<iostream>
#include<string>
#include<vector>
template<typename T>
class Vector2D
{
public:

	T x, y;

};


int main()
{

	Vector2D<int> *vec_0 = new Vector2D<int>;
	Vector2D<float> *vec_1 = new Vector2D<float>;
	Vector2D<double> *vec_2 = new Vector2D<double>;

	vec_0->x = 1;
	vec_0->y = 2;
	vec_1->x = 1.012342f;
	vec_1->y = 2.04f;
	vec_2->x = 1.001f;
	vec_2->y = 2.123f;

}