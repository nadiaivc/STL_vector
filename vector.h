#pragma once
#include <iostream>
using namespace std;
#define MAX_ELEMENTS 4294967295

template <typename T>
void myswap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
class myVector
{
public:

	class Iterator
	{

	private:

		T* main_mas;
		unsigned int Index;
		T* p;

	public:
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = random_access_iterator_tag;
		using size_type = std::size_t;

		Iterator()
		{
			Index = 0;
			p = nullptr;
			main_mas = nullptr;
		}

		Iterator(T* init_value, T* mas, size_type init_index)
		{
			main_mas = mas;
			p = init_value;
			Index = init_index;
		}

		~Iterator()
		{
			p = nullptr;
		}

		bool operator == (Iterator _iterator) const
		{
			return (p == _iterator.p) && (Index == _iterator.Index);
		}

		bool operator != (Iterator _iterator) const
		{
			return (p != _iterator.p) && (Index != _iterator.Index);
		}

		Iterator& operator++()
		{
			
				Index++;
				++p;
				return *this;
		}

		Iterator operator++(int)
		{
				Iterator key = (*this);
				++(*this);
				return key;
		}

		Iterator operator--(int)
		{
			if (Index >= 0) {
				Iterator key = (*this);
				--(*this);
				return key;
			}
		}

		Iterator& operator--()
		{
			if (Index >= 0) {
				Index--;
				--p;
				return *this;
			}
		}

		Iterator& operator += (size_type _value)
		{
			Index += _value;
			p = main_mas + Index;
			return *this;
		}

		Iterator& operator + (size_type _value)
		{
			Index += _value;
			p = main_mas + Index;
			return *this;
		}

		Iterator& operator -= (size_type _value)
		{
			Index -= _value;
			p = main_mas + Index;
			return *this;
		}

		Iterator& operator - (size_type _value)
		{
			Index -= _value;
			p = main_mas + Index;
			return *this;
		}

		bool operator < (Iterator _iterator) const
		{
			return (p < _iterator.p) && (Index < _iterator.Index);
		}

		bool operator <= (Iterator _iterator) const
		{
			return (p <= _iterator.p) && (Index <= _iterator.Index);
		}

		bool operator > (Iterator _iterator) const
		{
			return (p > _iterator.p) && (Index > _iterator.Index);
		}

		bool operator >= (Iterator _iterator) const
		{
			return (p >= _iterator.p) && (Index >= _iterator.Index);
		}

		difference_type operator-(Iterator _iterator) const
		{
			return this->p - _iterator.p;
		}

		difference_type operator+(Iterator _iterator) const
		{
			return this->p + _iterator.p;
		}

		unsigned int GetIndex()
		{
			return Index;
		}

		T& operator* ()
		{
			return *p;
		}
	};

	class reverse_Iterator
	{

	private:
		T* main_mas;
		unsigned int Index;
		T* p;

	public:
		using value_type = T;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using reverse_Iterator_category = random_access_iterator_tag;
		using size_type = std::size_t;

		reverse_Iterator()
		{
			Index = 0;
			p = nullptr;
			main_mas = nullptr;
		}

		reverse_Iterator(T* init_value, T* mas, size_type init_index)
		{
			main_mas = mas;
			p = init_value;
			Index = init_index;
		}

		~reverse_Iterator()
		{
			p = nullptr;
		}

		bool operator == (reverse_Iterator _reverse_Iterator) const
		{
			return (p == _reverse_Iterator.p) && (Index == _reverse_Iterator.Index);
		}

		bool operator != (reverse_Iterator _reverse_Iterator) const
		{
			return (p != _reverse_Iterator.p) && (Index != _reverse_Iterator.Index);
		}

		reverse_Iterator& operator--()
		{
				Index++;
				++p;
				return *this;
		}

		reverse_Iterator operator--(int)
		{
				reverse_Iterator key = (*this);
				--(*this);
				return key;
		}

		reverse_Iterator operator++(int)
		{
			if (Index >= 0) {
				reverse_Iterator key = (*this);
				++(*this);
				return key;
			}
		}

		reverse_Iterator& operator++()
		{
			if (Index >= 0) {
				Index--;
				--p;
				return *this;
			}
		}

		reverse_Iterator& operator -= (size_type _value)
		{
			Index += _value;
			p = main_mas + Index;
			return *this;
		}

		reverse_Iterator& operator - (size_type _value)
		{
			Index += _value;
			p = main_mas + Index;
			return *this;
		}

		reverse_Iterator& operator += (size_type _value)
		{
			Index -= _value;
			p = main_mas + Index;
			return *this;
		}

		reverse_Iterator& operator + (size_type _value)
		{
			Index -= _value;
			p = main_mas + Index;
			return *this;
		}

		bool operator < (reverse_Iterator _reverse_Iterator) const
		{
			return (p < _reverse_Iterator.p) && (Index < _reverse_Iterator.Index);
		}

		bool operator <= (reverse_Iterator _reverse_Iterator) const
		{
			return (p <= _reverse_Iterator.p) && (Index <= _reverse_Iterator.Index);
		}

		bool operator > (reverse_Iterator _reverse_Iterator) const
		{
			return (p > _reverse_Iterator.p) && (Index > _reverse_Iterator.Index);
		}

		bool operator >= (reverse_Iterator _reverse_Iterator) const
		{
			return (p >= _reverse_Iterator.p) && (Index >= _reverse_Iterator.Index);
		}

		difference_type operator+(reverse_Iterator _reverse_Iterator) const
		{
			return this->p - _reverse_Iterator.p;
		}

		difference_type operator-(reverse_Iterator _reverse_Iterator) const
		{
			return this->p + _reverse_Iterator.p;
		}

		unsigned int GetIndex(reverse_Iterator it)
		{
			return it.Index;
		}

		T& operator* ()
		{
			return *p;
		}
	};

	typedef T value_type;
	typedef T* pointer;
	typedef unsigned int size_type;

private:
	unsigned int my_size;
	unsigned int my_capacity;
	T* buffer;
	T* myfirst;
	T* mylast;
	T* myend;

public:
	myVector() :myfirst(0), mylast(0), myend(0), buffer(nullptr)
	{
		my_capacity = 0;
		my_size = 0;

	}

	myVector(unsigned int elements_number)
	{
		my_capacity = elements_number;
		my_size = my_capacity;
		allocate();
		mylast = myend;
	}

	myVector(unsigned int elements_number, T default_value)
	{
		my_size = elements_number;
		my_capacity = my_size;
		allocate();
		for (unsigned int i = 0; i < my_size; i++)
		{
			buffer[i] = default_value;
		}
	}

	~myVector()
	{
		if (buffer != nullptr) {
			delete[] buffer;
		}
		buffer = nullptr;
	}

	myVector(myVector& vector)//конструктор копии
	{
		my_size = vector.my_size;
		my_capacity = vector.my_capacity;
		myfirst = vector.myfirst;
		mylast = vector.mylast;
		myend = vector.myend;
		buffer = new T[my_size];
		for (int i = 0; i < my_size; i++)
			buffer[i] = vector.buffer[i];
	}

	void allocate()//берет все операции с new на себя при инициализации вектора
	{
		if (my_capacity <= MAX_ELEMENTS) {
			if (my_capacity == 0) {
				buffer = nullptr;
				myfirst = buffer;
				mylast = myfirst;
				myend = myfirst;

			}
			if (my_capacity > 0) {
				buffer = new T[my_capacity];
				myfirst = buffer;
				mylast = myfirst + my_capacity;
				myend = mylast;
			}
		}
	}

	myVector& operator = (const myVector& vec)
	{
		if (this == &vec)
			return *this;
		my_capacity = vec.my_size;
		my_size = vec.my_size;
		delete[] buffer;
		allocate();
		myfirst = vec.myfirst;
		mylast = vec.mylast;
		myend = vec.myend;
		for (int i = 0; i < my_size; ++i)
			buffer[i] = vec.buffer[i];
		return *this;
	}

	void assign(size_type n, const T& val)
	{
		my_capacity = n;
		my_size = 0;
		delete[] buffer;
		allocate();
		while (n != 0)
		{
			n--;
			push_back(val);
		}
	}

	//---------------------------------------------------//

	T& at(size_type index)
	{
		if (index < my_size)
			return buffer[index];
	}

	T& operator[](size_type index)
	{
		return buffer[index];
	}

	T& front()
	{
		return *myfirst;
	}

	T& back()
	{
		return *--mylast;
	}

	T* data()
	{
		return buffer;
	}

	//---------------------------------------------------//

	Iterator begin()
	{
		Iterator it(myfirst, myfirst, 0);
		return it;//first
	}

	Iterator end()
	{
		Iterator it(mylast, myfirst, my_size);
		return it;//next from last
	}

	reverse_Iterator rbegin()
	{
		reverse_Iterator it(--mylast, myfirst, my_size - 1);
		return it;
	}

	reverse_Iterator rend()
	{
		reverse_Iterator it(myfirst, myfirst, 0);
		return ++it;
	}

	//---------------------------------------------------//

	bool empty()
	{
		return (my_size == 0);
	}

	size_type size()const
	{
		return my_size;
	}

	size_type max_size() const
	{
		return MAX_ELEMENTS;
	}

	void reserve(size_type capacity)
	{
		if (capacity > my_capacity) {
			T* Newbuffer2 = new T[capacity];
			for (unsigned int i = 0; i < my_size; i++)
				Newbuffer2[i] = buffer[i];

			my_capacity = capacity;
			delete[] buffer;
			buffer = Newbuffer2;
			myfirst = buffer;
			mylast = myfirst + my_size;
			myend = myfirst + my_capacity;
		}
	}

	size_type capacity()const
	{
		return my_capacity;
	}

	void shrink_to_fit()
	{
		resize(my_size);
	}

	//---------------------------------------------------//

	void clear()
	{
		while (my_size != 0)
		{
			pop_back();
		}
	}

	Iterator insert(Iterator pos, T val)
	{
		if (my_size == my_capacity)
		{
			reserve(my_capacity + 5);
		}
		if (pos.GetIndex() < my_capacity) {
			if (my_size > 0) {
				for (size_type i = my_size - 1; i >= pos.GetIndex(); i--)
				{
					buffer[i + 1] = buffer[i];
					if (i == 0) break;//когда GetIndex = 0, i, и так равный 0, еще декрементируется, но вообще можно использовать и signed int i...
				}
			}
			buffer[pos.GetIndex()] = val;
			my_size++;
			++mylast;
			myVector<T>::Iterator it(myfirst + pos.GetIndex(), myfirst, pos.GetIndex());
			return it;
		}
	}

	template <typename...Types>
	void construct(pointer p, Types&&... t) {
		::new (static_cast<void*>(p)) T(std::forward<Types>(t)...);
	};

	template<typename ...Args>
	Iterator emplace_back(Args&&... args)
	{

		Iterator it = emplace(end(), std::forward<Args>(args)...);
		++mylast;
		return it;
	}

	template<typename ...Types>
	Iterator emplace(Iterator& it, Types&& ...args) {
		if (my_size + 1 > my_capacity) reserve(my_size + 1);
		

		if (it.GetIndex() < my_capacity) {
			if (my_size > 0) {
				for (size_type i = my_size - 1; i >= it.GetIndex(); i--)
				{
					buffer[i + 1] = buffer[i];
					if (i == 0) break;//когда GetIndex = 0, i, и так равный 0, еще декрементируется, но вообще можно использовать и signed int i...
				}

			}
			construct(myfirst + it.GetIndex(), std::forward<Types>(args)...);
			my_size++;
		}
		return it;
	}

	void destroy(pointer p) { p->~T(); };

	Iterator erase(Iterator pos)
	{
		if (my_size != 0)
		{
			if (pos.GetIndex() < my_capacity && pos.GetIndex() >= 0) {
				if (pos.GetIndex() == my_size - 1)
					destroy(buffer + my_size - 1);
				for (size_type i = pos.GetIndex(); i < my_size - 1; i++)
					buffer[i] = buffer[i + 1];
				myVector<T>::Iterator it(myfirst + pos.GetIndex(), myfirst, pos.GetIndex());
				my_size--;
				--mylast;
				if (pos.GetIndex() == 0)
					myfirst = buffer;
				return it;
			}

		}
	}

	void push_back(const T& elem)/////////////////////////////////////
	{
		if (my_size + 1 < MAX_ELEMENTS) {
			if (my_size == my_capacity)
				reserve(my_capacity + 5);
			buffer[my_size++] = elem;
			*mylast = buffer[my_size - 1];//////////////////////////////////////////////////////////////////////////
			++mylast;
			//*mylast = elem;

		}

	}

	void pop_back()////////////
	{

		erase(--end());
	}

	void resize(size_type size)
	{
		if (size <= MAX_ELEMENTS) {
			T* Newbuffer = new T[size];
			unsigned int size_t = size < my_size ? size : my_size;
			for (unsigned int i = 0; i < size_t; i++)
				Newbuffer[i] = buffer[i];
			if (size > my_capacity)
				my_capacity = size;
			if (size < my_size)
				my_size = size;
			delete[] buffer;
			buffer = Newbuffer;
			myfirst = buffer;
			mylast = myfirst + my_size;
			myend = myfirst + my_capacity;
			if (size > my_size) {
				while (my_size != size)
				{
					destroy(buffer + my_size);
					if (size > my_size)
						my_size++;
				}
			}
			mylast += size;
		}
	}

	void myswap(myVector<T>& rhs)
	{
		std::swap(my_size, rhs.my_size);
		std::swap(my_capacity, rhs.my_capacity);
		std::swap(buffer, rhs.buffer);
	}
	//---------------------------------------------------//

	bool lexicographical_compare(Iterator itr1_beg, Iterator itr1_end, Iterator itr2_beg, Iterator itr2_end)
	{
		itr1_end--; itr2_end--;
		if (&itr2_beg == nullptr) return false;
		if (&itr1_beg == nullptr) return false;

		while (itr1_beg != itr1_end && itr2_beg != itr2_end && *itr1_beg == *itr2_beg) {
			++itr1_beg;
			++itr2_beg;
		}

		if (&itr2_beg++ == nullptr) return false;
		if (&itr1_beg++ == nullptr) return true;
		itr1_beg--; itr2_beg--;
		if (itr2_beg == itr2_end) return false;
		if (itr1_beg == itr1_end) return true;

		if (*itr1_beg < *itr2_beg) return true;
		if (*itr1_beg > * itr2_beg) return false;

		return false;
	}

	bool operator < (myVector& a)
	{
		return a.lexicographical_compare(begin(), end(), a.begin(), a.end());
	}

	bool operator <= (myVector& a)
	{
		return !(*this > a);
	}

	bool operator > (myVector& a)
	{
		return a.lexicographical_compare(a.begin(), a.end(), begin(), end());
	}

	bool operator >= (myVector& a)
	{
		return !(*this < a);
	}

	bool operator != (myVector& a)
	{
		bool p, q;
		p = a.lexicographical_compare(a.begin(), a.end(), begin(), end());
		q = a.lexicographical_compare(begin(), end(), a.begin(), a.end());
		return (p + q);
	}

	bool operator == (myVector& a)
	{

		return !(*this != a);

	}

	//-------------------------- For Crossword ---------------------------
	void pushWithSort(const T& elem)//вставка элементов сразу в нужное место (сортировка по убыванию длины)
	{
		Iterator it = begin();
		try
		{
			if (my_size > 0) {
				int i = 0;
				while (elem.length() < buffer[i++].length() && it != end())
				{
					++it;
				}
			}
		}
		catch (int) {
			cout << "HEY! It's only for STRING!!!" << endl;
		}
		insert(it, elem);
	}

	void MySwap(int step, myVector& words2) {//перемешивание слов для образования новой базы, из которой\
											  попытаемся составить кроссворд
		int wordcount = words2.size();
		int i; int j;
		for (i = step, j = 0; i < wordcount; j++, i++)
		{
			buffer[j] = words2[i];
			if (j < step)
				buffer[wordcount - step + j] = words2[j];//составляем новую комбинацию расстановки слов
		}
	}
};
