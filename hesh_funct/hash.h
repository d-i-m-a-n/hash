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

	// вывод цепочки для соответствующего значения, если значений нет, выводим null
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
	// указатель одинарный, т.к. в списке есть указатель на голову
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
	// проверяем размерности таблиц, если одинаковые, то просто переписываем списки, если разные, то изменяем размерность
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
	// считаем индекс
	int idx = hashF(key, tab_size);
	// добавляем key в список под номером idx
	hash_tab[idx].AddToTail(key);
}

template<class X> int Hash<X>::Find(X& key)
{
	int i;
	// ищем номер списка, в котором содержится заданный ключ
	for (i = 0; i < tab_size && hash_tab[i].Find(key) == -1; i++);
	// проверяем по какому условию вышли из цикла
	// если дошли по циклу до конца, значит не нашли ни в 1 списке заданный ключ, возвращаем -1
	// если вышли по 2 условию, значит ключ в i-том списке, возвращаем i
	if (i != tab_size)
		return i;
	else
		return -1;
}

template<class X> bool Hash<X>::Del(X& key)
{
	int i;
	// ищем список, в котором находится ключ и удаляем, после удаления вернется true и мы выйдем из цикла
	for (i = 0; i < tab_size && !hash_tab[i].DelKey(key); i++);
	// проверяем по какому условию вышли из цикла
	// если дошли до конца, значит не нашли на в 1 списке заданный ключ, возвращаем false
	// если вышли раньше, значит в i-том списке удалили заданный ключ, возвращаем true
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