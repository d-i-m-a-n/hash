#pragma once
#include "C:\Users\Asus\source\repos\ConsoleApplication1\ConsoleApplication1\List.h"
#include <iostream>

template<class X> class Hash
{
public:
	
	Hash(int(*function)(X& key, int size), int Size);

	Hash(Hash<X>& obj);

	~Hash();

	Hash<X>& operator = (Hash<X>& obj);

	void Add(X& key);

	int Find(X& key);

	bool Del(X& key);

	void Clear();

	// ����� ������� ��� ���������������� ��������, ���� �������� ���, ������� null
	friend std::ostream& operator << (std::ostream& out, Hash<X>& obj)
	{
		for (int i = 0; i < obj.tab_size; i++)
		{
			out << i << ": ";
			if (obj.hash_tab[i])
				out << obj.hash_tab[i] << '\n';
			else
				out << "null\n";
		}
		return out;
	}

private:
	// ��������� ���������, �.�. � ������ ���� ��������� �� ������
	List<X> *hash_tab;
	int(*hashF)(X& key, int size);
	int tab_size;
};

template<class X> Hash<X>::Hash(int(*function)(X& key, int size), int size)
{
	hashF = function;
	tab_size = size;
	hash_tab = new List<X>[tab_size];
	if (!hash_tab)
		throw "memory error";

}

template<class X> Hash<X>::Hash(Hash<X>& obj)
{
	tab_size = obj.tab_size;
	hash_tab = new List<X>[tab_size];
	for (int i = 0; i < tab_size; hash_tab[i] = obj.hash_tab[i], i++);
}

template<class X> Hash<X>::~Hash()
{
	if(hash_tab)
		delete[] hash_tab;
	hash_tab = nullptr;
}

template<class X> Hash<X>& Hash<X>::operator = (Hash<X>& obj)
{
	// ��������� ����������� ������, ���� ����������, �� ������ ������������ ������, ���� ������, �� �������� �����������
	if (tab_size != obj.tab_size)
	{
		delete[] hash_tab;

		tab_size = obj.tab_size;
		hash_tab = new List<X>[size];
	}
	for (int i = 0; i < size; hash_tab[i] = obj.hash_tab[i], i++);
}

template<class X> void Hash<X>::Add(X& key)
{
	// ������� ������
	int idx = hashF(key, tab_size);
	// ��������� key � ������ ��� ������� idx
	hash_tab[idx].AddToTail(key);
}

template<class X> int Hash<X>::Find(X& key)
{
	int i;
	// ���� ����� ������, � ������� ���������� �������� ����
	for (i = 0; i < tab_size && hash_tab[i].Find(key) == -1; i++);
	// ��������� �� ������ ������� ����� �� �����
	// ���� ����� �� ����� �� �����, ������ �� ����� �� � 1 ������ �������� ����, ���������� -1
	// ���� ����� �� 2 �������, ������ ���� � i-��� ������, ���������� i
	if (i != tab_size)
		return i;
	else
		return -1;
}

template<class X> bool Hash<X>::Del(X& key)
{
	int i;
	// ���� ������, � ������� ��������� ���� � �������, ����� �������� �������� true � �� ������ �� �����
	for (i = 0; i < tab_size && !hash_tab[i].DelKey(key); i++);
	// ��������� �� ������ ������� ����� �� �����
	// ���� ����� �� �����, ������ �� ����� �� � 1 ������ �������� ����, ���������� false
	// ���� ����� ������, ������ � i-��� ������ ������� �������� ����, ���������� true
	if (i == tab_size)
		return false;
	else
		return true;
}

template<class X> void Hash<X>::Clear()
{
	for (int i = 0; i < tab_size; i++)
		hash_tab[i].Clear();
}