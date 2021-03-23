#ifndef ARRAY_H
#define ARRAY_H

#pragma warning(disable : 4996)

#include <memory>
#include <utility>
#include <stdexcept>

class ARRAY_OUT_OF_BOUNDS {};
class ARRAY_FITTING_ISSUE {};
class ARRAY_FULL {};
class ARRAY_INIT_OUT_OF_RANGE {};

template <typename T, size_t size>
class Array {
public:
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	Array();
	Array(const Array& other);
	Array(const std::initializer_list<T>& init_list);
	~Array();

	//const size_t size() const noexcept{ return _size;  }
	//size_t size() { return _size; }

	size_t capacity() const { return _size; }
	size_t count();
	const size_t count() const;
	T* data() noexcept { return _array; }
	const T* data() const noexcept { return _array; }

	void push_back(const T& val);
	void clear() noexcept { _end = _start; }

	const T& front() const;
	T& front();
	const T& back() const;
	T& back();
	T& at(size_t indx);
	const T& at(size_t indx) const;
	constexpr bool full() { 
		if ((_end - _start) == _size)
			return true;
		return false;
	}

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const;
	reverse_iterator rbegin() noexcept;
	const_reverse_iterator crbegin() const noexcept;
	reverse_iterator rend() noexcept;
	const_reverse_iterator crend() const noexcept;

	template<typename... ARGS>
	T& emplace_back(ARGS... args);
	template<typename... ARGS>
	iterator emplace(const T* pos, ARGS&&... args);
	iterator insert(iterator pos, const T& val);
	iterator insert(const_iterator pos, const T& val);
	iterator insert(const_iterator pos, T&& val);


	T& operator[](const size_t& indx);
	const T& operator[](const size_t& indx) const;
	Array& operator=(Array& other);

	bool operator==(const Array& rhs);
	const bool operator==(const Array& rhs) const;

private:
	T _array[size];
	size_t _size = size;
	
	T *_start, *_end;
};

template<typename T, size_t size>
inline Array<T, size>::Array()
{
	if (_size > 0) {
		_start = _end = &_array[0];
	}
	else
		_start = _end = nullptr;
}

template<typename T, size_t size>
inline Array<T, size>::Array(const Array& other)
{
	if (other._size > _size)
		throw ARRAY_FITTING_ISSUE{};
	for (int i = 0; i < other.capacity(); i++) {
		_array[i] = other._array[i];
		++_end;
	}

}

template<typename T, size_t size>
inline Array<T, size>::Array(const std::initializer_list<T>& init_list)
{
	int i_size = init_list.size();
	if (i_size > _size)
		throw ARRAY_INIT_OUT_OF_RANGE {};
	int i = 0;
	for (auto iter = init_list.begin(); iter != init_list.end(); i++, ++iter) {
		_array[i] = *iter;
		_end++;
	}
}

template<typename T, size_t size>
inline Array<T, size>::~Array()
{
	//delete[] _array;
}

template<typename T, size_t size>
inline size_t Array<T, size>::count()
{
	return (_end - _start);
}

template<typename T, size_t size>
inline const size_t Array<T, size>::count() const
{
	return (_end - _start);
}

template<typename T, size_t size>
inline void Array<T, size>::push_back(const T& val)
{
	//If the array is not full
	size_t pos = _end - _start;
	if (pos < _size) {
		_array[pos] = val;
		++_end;
	}
	else
		throw ARRAY_FULL{};
}

template<typename T, size_t size>
inline const T& Array<T, size>::front() const
{
	return &_array[0];
}

template<typename T, size_t size>
inline T& Array<T, size>::front()
{
	return &_array[0];
}

template<typename T, size_t size>
inline const T& Array<T, size>::back() const
{
	return &_array[_size - 1];
}

template<typename T, size_t size>
inline T& Array<T, size>::back()
{
	return &_array[_size-1];
}

template<typename T, size_t size>
inline T& Array<T, size>::at(size_t indx)
{
	if (indx >= _size || indx < 0)
		throw std::out_of_range("Out of range");

	return &_array[indx];
}

template<typename T, size_t size>
inline const T& Array<T, size>::at(size_t indx) const
{
	if (indx >= _size || indx < 0)
		throw std::out_of_range("Out of range");

	return &_array[indx];
}

template<typename T, size_t size>
inline typename Array<T, size>::iterator Array<T, size>::begin() noexcept
{
	return _start;
}

template<typename T, size_t size>
inline typename Array<T, size>::const_iterator Array<T, size>::begin() const noexcept
{
	return _start;
}

template<typename T, size_t size>
inline typename Array<T, size>::iterator Array<T, size>::end() noexcept
{
	return _start + _size;
}

template<typename T, size_t size>
inline typename Array<T, size>::const_iterator Array<T, size>::end() const noexcept
{
	return _start + _size;
}

template<typename T, size_t size>
inline typename Array<T, size>::const_iterator Array<T, size>::cbegin() const noexcept
{
	return _start;
}

template<typename T, size_t size>
inline typename Array<T, size>::const_iterator Array<T, size>::cend() const
{
	return _start + _size;
}

template<typename T, size_t size>
inline typename Array<T, size>::reverse_iterator Array<T, size>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template<typename T, size_t size>
inline typename Array<T, size>::const_reverse_iterator Array<T, size>::crbegin() const noexcept
{
	return rbegin();
}

template<typename T, size_t size>
inline typename Array<T, size>::reverse_iterator Array<T, size>::rend() noexcept
{
	return reverse_iterator(begin());
}

template<typename T, size_t size>
inline typename Array<T, size>::const_reverse_iterator Array<T, size>::crend() const noexcept
{
	return rend();
}

template<typename T, size_t size>
inline typename Array<T, size>::iterator Array<T, size>::insert(iterator pos, const T& val)
{
	return iterator();
}

template<typename T, size_t size>
inline typename Array<T, size>::iterator Array<T, size>::insert(const_iterator pos, const T& val)
{
	return iterator();
}

template<typename T, size_t size>
inline typename Array<T, size>::iterator Array<T, size>::insert(const_iterator pos, T&& val)
{
	return iterator();
}

template<typename T, size_t size>
inline T& Array<T, size>::operator[](const size_t& indx)
{
	if (indx > _size || indx < 0)
		throw ARRAY_OUT_OF_BOUNDS{};

	return _array[indx];
}

template<typename T, size_t size>
inline const T& Array<T, size>::operator[](const size_t& indx) const
{
	if (indx > size || indx < 0)
		throw ARRAY_OUT_OF_BOUNDS{};

	return &_array[indx];
}

template<typename T, size_t size>
inline Array<T,size>& Array<T, size>::operator=(Array& other)
{
	if (other._size != this->_size)
		throw ARRAY_FITTING_ISSUE{};

	_end = _start;
	for (auto i = 0; i < other.capacity(); i++) {
		_array[i] = other[i];
	}

	for (auto i = 0; i < other.count(); i++) {
		_end++;
	}

	return *this;
}

template<typename T, size_t size>
inline bool Array<T, size>::operator==(const Array& rhs)
{
	if (this->_size != rhs._size || this->count() != rhs.count())
		return false;

	for (auto i = 0; i < this->_size; i++) {
		if (this->_array[i] != rhs[i])
			return false;
	}
	return true;
}

template<typename T, size_t size>
inline const bool Array<T, size>::operator==(const Array& rhs) const
{
	if (this->_size != rhs._size || this->count() != rhs.count())
		return false;

	for (auto i = 0; i < this->_size; i++) {
		if (this->_array[i] != rhs[i])
			return false;
	}
	return true;
}

template<typename T, size_t size>
template<typename... ARGS>
inline T& Array<T, size>::emplace_back(ARGS ...args)
{
	if (full())
		throw ARRAY_FULL{};

	_end++;
	_array[count()] = std::move(T(std::forward<ARGS>(args)...));
	return _array[count()];
}

template<typename T, size_t size>
template<typename ...ARGS>
inline typename Array<T, size>::iterator Array<T, size>::emplace(const T* pos, ARGS && ...args)
{
	return iterator();
}

#endif
