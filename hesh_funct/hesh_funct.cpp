// hesh_funct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hash.h"
#include <iostream>

// простейшие функции хэширования, были представленны в лекции
template<class X> int div_hashF(X& key, int size)
{
	return key%size;
}

template<class X> int mul_hashF(X& key, int size)
{
	float a = (sqrt(5) - 1) / 2;
	return  (int)floor(key*a*size) % size;
}

int main()
{
	int x[5] = { 31,15,7,3,1 };
	Hash<int> hash1(div_hashF, 10);
	std::cout << hash1 << '\n';

	for (int i = 0; i < 5; hash1.Add(x[i]), i++);
	std::cout << hash1 << '\n';

	std::cout << hash1.Find(x[4]) << "\n\n";

	hash1.Del(x[4]);
	std::cout << hash1 << '\n';

	hash1.Clear();
	std::cout << hash1 << '\n';

	Hash<int> hash2(mul_hashF, 10);
	for (int i = 0; i < 5; hash2.Add(x[i]), i++);
	std::cout << hash2;

	return 0;
}