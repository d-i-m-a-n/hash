#pragma once
#include "stdafx.h"
#include <iostream>

template<class X> class List
{
public:
	class Node
	{
	public:
		X data;
		Node* next;
		Node* prev;
	};

	List()
	{
		size = 0;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
	}

	List(X* mas, int N)
	{
		if (mas && N > 0)
		{
			size = N;
			head = new Node;
			head->data = *mas;
			head->prev = nullptr;
			current = head;

			for (int i = 1; i < N; i++)
			{
				current->next = new Node;
				current->next->prev = current;
				current = current->next;
				current->data = mas[i];
			}
			current->next = nullptr;
			tail = current;
			current = head;
		}
		else
		{
			size = 0;
			head = nullptr;
			tail = nullptr;
			current = nullptr;
		}
	}

	List(List<X>& obj)
	{
		size = obj.size;

		if (obj.head)
		{
			Node* ptr = obj.head, *ptr2 = nullptr;
			head = new Node;
			if (ptr == obj.current)
				current = head;

			head->data = ptr->data;
			head->prev = nullptr;
			ptr2 = head;

			while (ptr = ptr->next)
			{
				ptr2->next = new Node;
				if (ptr == obj.current)
					current = ptr2->next;
				ptr2->next->data = ptr->data;
				ptr2->next->prev = ptr2;
				ptr2 = ptr2->next;
			}

			ptr2->next = nullptr;
			tail = ptr2;
		}
		else
		{
			head = nullptr;
			tail = nullptr;
			current = nullptr;
		}
	}

	~List()
	{
		if (head)
		{
			current = tail->prev;
			do
			{
				delete current->next;
			} while (current = current->prev);
			delete head;

			head = current = tail = nullptr;
			size = 0;
		}
	}

	void AddToHead(X& DATA)
	{
		size++;
		if (head)
		{
			Node* ptr = head;

			head = new Node;
			head->data = DATA;
			head->next = ptr;
			head->prev = nullptr;
			ptr->prev = head;

			if (current != tail)
				current = current->prev;

		}
		else
		{
			head = new Node;
			head->data = DATA;
			head->next = nullptr;
			head->prev = nullptr;
			tail = current = head;
		}
	}

	void AddToTail(X& DATA)
	{
		size++;
		if (head)
		{
			Node* ptr = tail;

			tail = new Node;
			tail->data = DATA;
			tail->next = nullptr;
			tail->prev = ptr;
			ptr->next = tail;

			if (head->next != tail)
			{
				if (current->next == tail)
					current = current->next;
			}
		}
		else
		{
			head = new Node;
			head->data = DATA;
			head->next = nullptr;
			head->prev = nullptr;
			current = tail = head;
		}
	}

	void AddAfterCurrent(X& DATA)
	{
		size++;
		if (head)
		{
			Node* ptr = current->next;

			current->next = new Node;
			current->next->data = DATA;
			current->next->next = ptr;
			current->next->prev = current;

			if (ptr)
				ptr->prev = current->next;
			else
				tail = current->next;

			if (head->next != tail)
			{
				if (current->next == tail)
					current = current->next;
			}

		}
		else
		{
			head = new Node;
			head->data = DATA;
			head->next = nullptr;
			head->prev = nullptr;
			tail = current = head;
		}
	}

	void AddBeforeCurrent(X& DATA)
	{
		size++;
		if (head)
		{
			Node* ptr = current->prev;

			current->prev = new Node;
			current->prev->data = DATA;
			current->prev->next = current;
			current->prev->prev = ptr;

			if (ptr)
				ptr->next = current->prev;
			else
				head = current->prev;

			if (current != tail)
				current = current->prev;

		}
		else
		{
			head = new Node;
			head->data = DATA;
			head->next = nullptr;
			head->prev = nullptr;
			tail = current = head;
		}
	}

	bool DelFromHead()
	{
		if (head)
		{
			size--;
			Node* ptr = head->next;

			if (current == head)
				current = ptr;

			delete head;

			head = ptr;
			head->prev = nullptr;
			return true;
		}
		return false;
	}

	bool DelFromTail()
	{
		if (tail)
		{
			size--;
			Node* ptr = tail->prev;

			if (current == tail)
				current = ptr;

			delete tail;

			tail = ptr;
			tail->next = nullptr;
			return true;
		}
		return false;
	}

	bool DelKey(X& DATA)
	{

		Node* ptr = head;

		while (ptr)
		{
			if (ptr->data == DATA)
			{
				size--;
				if (ptr == head)
					head = ptr->next;

				if (ptr == tail)
					tail = ptr->prev;

				if (ptr == current)
					if (ptr->next)
						current = ptr->next;
					else
						current = ptr->prev;

				Node* NEXT = ptr->next;
				Node* PREV = ptr->prev;

				delete ptr;

				if (NEXT)
					NEXT->prev = PREV;
				if (PREV)
					PREV->next = NEXT;

				return true;
			}
			ptr = ptr->next;
		}
		return false;
	}

	bool DelCurrent()
	{
		if (current)
		{
			size--;
			Node* ptr = current;

			if (ptr == head)
				head = ptr->next;

			if (ptr == tail)
				tail = ptr->prev;

			if (ptr->prev)
				current = ptr->prev;
			else
				current = ptr->next;

			if (ptr->next)
				ptr->next->prev = ptr->prev;
			if (ptr->prev)
				ptr->prev->next = ptr->next;

			delete ptr;

			return true;
		}
		return false;
	}

	bool MoveCurrentToHead()
	{
		if (head)
		{
			current = head;
			return true;
		}
		return false;
	}

	bool MoveCurrentToTail()
	{
		if (tail)
		{
			current = tail;
			return true;
		}
		return false;
	}

	bool MoveCurrentToPos(int i)
	{
		if (i < size && i > -1)
		{
			current = head;
			for (int j = 0; j < i; current = current->next, j++);
			return true;
		}
		return false;
	}

	bool MoveCurrentForward()
	{
		if (current->next)
		{
			current = current->next;
			return true;
		}
		return false;
	}

	bool MoveCurrentBackward()
	{
		if (current->prev)
		{
			current = current->prev;
			return true;
		}
		return false;
	}

	X& GetCurrent()
	{
		if (current)
			return current->data;
		throw "error";
	}

	int GetSize()
	{
		return size;
	}

	int Find(X& DATA)
	{
		Node* ptr = head;
		int k = 0;

		while (ptr)
		{
			if (ptr->data == DATA)
				return k;
			k++;
			ptr = ptr->next;
		}
		return -1;
	}

	void Clear()
	{
		Node* ptr1 = tail, *ptr2;

		while (ptr1)
		{
			ptr2 = ptr1->prev;
			delete ptr1;
			ptr1 = ptr2;
		}

		head = tail = current = nullptr;
		size = 0;
	}

	List<X>& operator = (List<X>& obj)
	{
		Node* ptr1 = head, *ptr2 = obj.head;

		size = obj.size;

		while (ptr1 && ptr2)
		{
			if (ptr2 == obj.current)
				current = ptr1;
			ptr1->data = ptr2->data;
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}

		if (ptr1 && !ptr2)
		{
			if (ptr1->prev)
				ptr1->prev->next = nullptr;
			if (ptr1 == head)
				head = current = nullptr;
			tail = ptr1->prev;

			do
			{
				ptr2 = ptr1->next;
				delete ptr1;
				ptr1 = ptr2;
			} while (ptr1);
		}

		if (ptr2 && !ptr1)
		{
			ptr1 = tail;
			if (!head)
			{
				head = new Node;
				if (ptr2 == obj.current)
					current = head;
				head->data = ptr2->data;
				head->prev = nullptr;
				ptr1 = head;
				ptr2 = ptr2->next;
			}

			do
			{
				ptr1->next = new Node;
				if (ptr2 == obj.current)
					current = ptr1;
				ptr1->next->data = ptr2->data;
				ptr1->next->prev = ptr1;
				ptr1 = ptr1->next;
			} while (ptr2 = ptr2->next);

			ptr1->next = nullptr;
			tail = ptr1;
		}

		return *this;
	}

	bool operator == (List<X>& obj)
	{
		if (size == obj.size)
		{
			Node* ptr1 = head;
			Node* ptr2 = obj.head;

			while (ptr1 && ptr1->data == ptr2->data)
			{
				ptr1 = ptr1->next;
				ptr2 = ptr2->next;
			}

			if (!ptr1)
				return true;
		}
		return false;
	}

	List<X> operator + (List<X>& obj)
	{
		List<X> res(*this);

		if (obj.head)
		{
			res.size += obj.size;
			Node* ptr = obj.head;
			res.current = res.tail;

			do
			{
				res.current->next = new Node;
				res.current->next->data = ptr->data;
				res.current->next->next = nullptr;
				res.current->next->prev = res.current;

				res.current = res.current->next;
			} while (ptr = ptr->next);
			res.current = res.head;
		}
		return res;
	}

	List<X>& operator += (List<X>&)
	{
		if (obj.head)
		{
			size += obj.size;
			Node* ptr = obj.head;
			current = tail;

			for (int i = 0; i < obj.size; i++)
			{
				current->next = new Node;
				current->next->data = ptr->data;
				current->next->next = nullptr;
				current->next->prev = current;

				current = current->next;
				ptr = ptr->next;
			}
		}
		return *this;
	}

	operator bool()
	{
		if (head)
			return true;
		return false;
	}

	friend std::istream& operator >> (std::istream& in, List<X>& obj)
	{
		int N;
		in >> N;
		in.get();
		if (N > 0)
		{
			obj.size = N;
			Node* ptr = obj.head;

			while (N && ptr)
			{
				in >> ptr->data;
				N--;
				ptr = ptr->next;
			}

			if (ptr && !N)
			{
				if (ptr->prev)
					ptr->prev->next = nullptr;
				if (ptr == obj.head)
					obj.head = obj.current = nullptr;
				obj.tail = ptr->prev;
				Node* ptr2;
				do
				{
					ptr2 = ptr->next;
					delete ptr;
					ptr = ptr2;
				} while (ptr);
			}

			if (N && !ptr)
			{
				ptr = obj.tail;
				if (!obj.head)
				{
					obj.head = new Node;
					in >> obj.head->data;
					obj.head->prev = nullptr;
					ptr = obj.head;
					N--;
				}

				do
				{
					ptr->next = new Node;
					in >> ptr->next->data;
					ptr->next->prev = ptr;
					ptr = ptr->next;
				} while (--N);

				ptr->next = nullptr;
				obj.tail = ptr;
			}

			obj.current = obj.head;
		}
		else
			if (N == 0)
				obj.Clear();
		return in;
	}

	friend std::ostream& operator << (std::ostream& out, List<X>& obj)
	{
		Node* ptr = obj.head;

		while (ptr)
		{
			out << ptr->data << ' ';
			ptr = ptr->next;
		}
		return out;
	}

protected:
	int size;
	Node* head;
	Node* tail;
	Node* current;
};