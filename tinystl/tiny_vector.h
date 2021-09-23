#ifndef CN_HUST_LYH_TINYVECTOR_H
#define CN_HUST_LYH_TINYVECTOR_H

#include <iostream>
#include "util.h"
using util::println;

/// <summary>
/// 
/// �ӿ������Լ��������Ͳο���http://www.cplusplus.com/reference/vector/vector/?kw=vector
/// 
/// </summary>

namespace tstd {

template<typename T>
class vector {
public:

	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using size_type = size_t;
	using iterator = value_type*;
	using const_iterator = value_type*;

	
#pragma region Capacity

	size_type size() const noexcept{
		return static_cast<size_type>(_end - _begin);
	}

	size_type max_size() const noexcept {
		static_cast<size_type>(-1) / sizeof(T);
	};

	size_type capacity() const noexcept{
		return static_cast<size_type>(_cap - _begin);
	}

	void resize() { // TODO[lyh][0]: resize
		;
	}

	bool empty() const noexcept{
		return _begin == _end;
	}

	void reserve(size_type n) {// TODO[lyh][0]: reserve
	
	}

	void shrink_to_fit() {// TODO[lyh][0]: shrink_to_fit

	}

#pragma endregion

#pragma region ElementAccess

	reference operator [](size_t index) noexcept{
		return *(_begin + index);
	}
	
	const_reference operator [](size_t index) const noexcept{
		return *(_begin + index);
	}

	reference at(size_type n) {
		return *(_begin + n);
	}

	const_reference at(size_type n) const {
		return *(_begin+n);
	}

	reference front() {
		return *_begin;
	}
	const_reference front() const {
		return *_begin;
	}
	
	reference back() {
		return *(_end-1);
	}

	const_reference back() const {
		return *(_end-1);
	}

	value_type* data() noexcept {
		return _begin;
	}

	const value_type* data() const noexcept {
		return _begin;
	}

#pragma endregion

	vector();
	vector(size_type n);
	vector(size_type n, value_type val);
	vector(std::initializer_list<value_type> li);

	vector(const vector& lval);
	vector(vector&& rval) noexcept;

	vector& operator = (const vector& lval);
	vector& operator = (vector&& rval) noexcept;

	bool expand();

	void push_back(const_reference val);

	
#pragma region Iterators:

	iterator begin() noexcept {
		return _begin;
	}

	const_iterator begin() const noexcept {
		return _begin;
	}
	
	iterator end() noexcept {
		return _end;
	}

	const_iterator end() const noexcept {
		return _end;
	}

#pragma endregion

	~vector();
private:

	iterator _begin;
	iterator _end;
	iterator _cap;

	pointer allocate(size_type n);
};

template<typename T>
bool vector<T>::expand() {
	
	println("call:expand()");
	size_type new_size = std::max(size() + 1, capacity() * 2);
	auto new_begin = allocate(new_size);
	auto new_end = new_begin;
	auto new_cap = new_begin + new_size;

	for (auto i = _begin; i != _end; ++i) {
		*new_end = *i;
		++new_end;
	}
	delete [] _begin;

	_begin = new_begin;
	_end = new_end;
	_cap = new_cap;

	return true;
}


template<typename T>
void vector<T>::push_back(const_reference val) {
	if (_end == _cap) {
		expand();
	}
	else {
		*_end = val;
		++_end;
	}
}

//template<typename T>
//void vector<T>::show() {
//	std::cout << "[";
//	for (iterator it = _begin; it != _end; ++it) {
//		std::cout << *it << ",";
//	}
//	std::cout << "]" << std::endl;
//}

template<typename T>
vector<T>::vector() :_begin(nullptr), _end(nullptr), _cap(nullptr) {
	println("call: Vector()");
}

template<typename T>
vector<T>::vector(size_type n) {
	println("call:Vector(size_t _len)");
	_begin = allocate(n);
	_end = _begin + n;
	_cap = _begin + n;
	std::fill(_begin, _end, value_type());
}

template<typename T>
vector<T>::vector(std::initializer_list<value_type> li) {

	println("call:Vector(std::initializer_list<value_type> li)");

	size_type n = li.end() - li.begin();

	_begin = allocate(n);
	_end = begin();
	_cap = _begin + n;
	for (auto& i : li) {
		*_end = i;
		++_end;
	}
}

template<typename T>
vector<T>::vector(size_type n, value_type val) {

	println("call:Vector(size_t _len, int val)");
	_begin = allocate(n);
	_end = _begin + n;
	_cap = _begin + n;
	std::fill(_begin, _end, val);
}

template<typename T>
vector<T>::vector(const vector<T>& lval) {

	println("call:Vector(const Vector& lval)");
	size_type n = lval.size();
	_begin = allocate(n);
	_end = _begin + n;
	_cap = _begin + n;

	for (size_t i = 0; i < lval.size(); ++i) {
		(*this)[i] = lval[i];
	}
}

template<typename T>
vector<T>::vector(vector<T>&& rval) noexcept :_begin(rval._begin), _end(rval._end), _cap(rval._cap) {

	println("call:Vector(Vector&& rval) noexcept");
	rval._begin = nullptr;
	rval._end = nullptr;
	rval._cap = nullptr;
}

template<typename T>
vector<T>& vector<T>::operator = (const vector<T>& lval) {

	println("call:operator =(const Vector& lval)");

	if (this != &lval) {
		delete[] _begin;
		size_type n = lval.size();
		_begin = allocate(n);
		_end = _begin + n;
		_cap = _begin + n;

		for (size_t i = 0; i < lval.size(); ++i) {
			(*this)[i] = lval[i];
		}
	}

	return *this;
}

template<typename T> 
vector<T>& vector<T>::operator = (vector<T>&& rval) noexcept {

	println("call:operator =(Vector&& rval) noexcept");

	if (this != &rval) {
		delete[] _begin;
		_begin = rval._begin;
		_end = rval._end;
		_cap = rval._cap;

		rval._begin = nullptr;
		rval._end = nullptr;
		rval._cap = nullptr;
	}
	return *this;
}

template<typename T>
typename vector<T>::pointer
vector<T>::allocate(size_type n) {
	if (n == 0)
		return nullptr;
	return static_cast<pointer>(::operator new(n * sizeof(value_type)));
}

template<typename T>
vector<T>::~vector() {

	println("call:~Vector()");
	println("_begin", _begin);
	println("_begin == nullptr",_begin == nullptr);
	if (_begin) {

		delete[]  _begin;

		_begin = nullptr;
		_end = nullptr;
		_cap = nullptr;
	}
}

}

#endif // !CN_HUST_LYH_TINYVECTOR_H