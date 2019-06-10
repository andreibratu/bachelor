#include <utility>

#ifndef HEAP_H
#define HEAP_H

#include <utility>
#include <algorithm>
#include <functional>

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

typedef std::function<bool(TPriority, TPriority)> Comp;

template <class T>
class Heap {
private:
	int capacity{};
	int l_size{};
	T* elements;
	Comp relation;

	void bubble_up(int pos);

	void bubble_down(int pos);

	void resize();
public:
	

	Heap();

	explicit Heap(Comp  r);

	void add(T e);

	Heap(const Heap & h);

	Heap& operator = (const Heap& that);
	T top() const;

	T remove();

	int size() const;

	bool empty() const;

	~Heap();
};

//O(1)
template<class T>
Heap<T>::Heap(Comp r) : relation{ std::move(r) }
{
	this->capacity = 50;
	this->elements = new T[this->capacity];
	this->l_size = 0;
}

//O(log n)
template<class T>
inline void Heap<T>::add(T e)
{
	if (this->capacity == this->l_size)
		this->resize();
	this->elements[this->l_size] = e;
	this->bubble_up(this->l_size);
	this->l_size++;
}

//theta(n)=O(n)
template <class T>
Heap<T>::Heap(const Heap& h) {
	this->capacity = h.capacity;
	this->l_size = h.l_size;
	this->elements = new T[this->capacity];
	std::copy(h.elements + 0, h.elements + l_size, this->elements);
	this->relation = h.relation;
};

//O(log n)
template<class T>
inline T Heap<T>::remove()
{
	if (this->l_size == 0)
	{
		throw std::logic_error("Empty heap!");
	}
	T deleted = this->elements[0];
	this->elements[0] = this->elements[this->l_size - 1];
	this->l_size--;
	this->bubble_down(0);
	return deleted;
}

template<class T>
Heap<T>::~Heap()
{
	
	delete[] this->elements;
}


//O(log n)
template<class T>
inline void Heap<T>::bubble_up(int pos)
{
	int parent_idx = (pos - 1) / 2;
	while (pos != 0 && this->relation(this->elements[pos].second, this->elements[parent_idx].second))
	{
		swap(this->elements[parent_idx], this->elements[pos]);
		pos = parent_idx;
		parent_idx = (pos - 1) / 2;

	}
}

//O(log n)
template<class T>
inline void Heap<T>::bubble_down(int pos)
{
	T parent = this->elements[pos];
	while (pos < this->l_size)
	{
		int max_child = -1;

		if (pos * 2 + 1 <= this->l_size && this->relation(
			this->elements[2 * pos + 1].second,
			this->elements[2 * pos + 2].second
		))
		{
			max_child = pos * 2 + 1;

		}

		if (pos * 2 + 2 <= this->l_size && this->relation(
			this->elements[2 * pos + 2].second,
			this->elements[2 * pos + 1].second
		))
		{
			max_child = pos * 2 + 2;
		}

		if (max_child != -1 && this->relation(this->elements[max_child].second, parent.second))
		{
			swap(this->elements[pos],this->elements[max_child]);
			pos = max_child;
		}
		else
		{
			pos = this->l_size;
		}
	}
}

//theta(n)=O(n)
template<class T>
void Heap<T>::resize()
{
	this->capacity *= 2;
	T* new_elements = new T[this->capacity];
	std::copy(this->elements + 0, this->elements + this->l_size, new_elements + 0);
	delete[] this->elements;
	this->elements = new_elements;
}


template<class T>
Heap<T>::Heap() {
	this->capacity = 1;
	this->l_size = 0;
	this->elements = new T[this->capacity];
}

//theta(1)
template<class T>
int Heap<T>::size() const {
	return this->l_size;
}

//theta(n)=O(n)
template<class T>
inline Heap<T>& Heap<T>::operator=(const Heap & that)
{
	if (this == &that)
		return *this;
	this->capacity = that.capacity;
	this->l_size = that.l_size;

	delete[] this->elements;

	this->elements = new T[this->capacity];
	std::copy(that.elements + 0, that.elements + this->l_size, this->elements);
	this->relation = that.relation;

	return *this;
}

//theta(1)
template<class T>
T Heap<T>::top() const {
	if (this->empty()) throw std::logic_error("Ce facusi mai nene ma");
	return this->elements[0];
}
//theta(1)
template<class T>
bool Heap<T>::empty() const {
	return this->size() == 0;
}

#endif
