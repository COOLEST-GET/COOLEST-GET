#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>


class MyString
{
public:
	// 构造函数
	explicit MyString(const char* str = "") 
		:_size(strlen(str))
	{
		_capacity = _size == 0 ? 3 : _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	MyString(const MyString& str)
		:_size(str._size),
		 _capacity(str._capacity)
	{
		_str = new char[_capacity + 1];
		strcpy(_str, str._str);
	}

	MyString(MyString&& str) noexcept
		:_size(str._size),
		 _capacity(str._capacity),
		 _str(str._str)
	{
		str._capacity = 0;
		str._size = 0;
		str._str = nullptr;
	}

	// 析构函数
	~MyString()
	{
		delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	// 迭代器
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin() const
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	// 容量相关
	size_t size() const
	{
		return _size;
	}

	size_t capacity() const
	{
		return _capacity;
	}

	bool empty() const
	{
		return _size == 0;
	}

	void clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}

	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = nullptr;
			_capacity = n;
		}
	}

	void resize(size_t n, char ch = '\0')
	{
		if (n < _size)
		{
			_size = n;
			_str[_size] = '\0';
		}
		else
		{
			if (n > _capacity)
			{
				reserve(n);
			}
			for (size_t i = _size; i < n; ++i)
			{
				_str[i] = ch;
			}
			_size = n;
			_str[_size] = '\0';
		}
	}

	// 访问元素
	char& operator[](size_t pos)
	{
		assert(pos <= _size);
		return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos <= _size);
		return _str[pos];
	}

	char& front()
	{
		return (*this)[0];
	}

	const char& front() const
	{
		return (*this)[0];
	}

	char& back()
	{
		return (*this)[_size - 1];
	}

	const char& back() const
	{
		return (*this)[_size - 1];
	}

	const char* c_str() const
	{
		return _str;
	}

	// 修改操作
	void push_back(char ch)
	{
		if (_size > _capacity)
		{
			reserve(_capacity * 2);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	void append(const char* str)
	{
		if (str == nullptr) 
		{
			return;
		}

		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}

		strcpy(_str + _size, str);
		_size += len;
	}

	void push_back(const char* str)
	{
		return append(str);
	}

	MyString& insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size + 1 > _capacity)
		{
			reserve(_capacity * 2);
		}

		for (size_t i = _size + 1; i < pos; --i)
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = ch;
		++_size;
		return *this;
	}

	MyString& insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}

		for (size_t i = _size + len; i > pos + len - 1; --i)
		{
			_str[i] = _str[i - len];
		}

		strcpy(_str + pos, str);
		_size += len;
		_str[_size] = '\0';
		return *this;
	}

	MyString& erase(size_t pos, size_t len = static_cast<size_t>(-1))
	{

	}


	// 查找操作

	// 运算符重载




private:
	char* _str;
	size_t _size;
	size_t _capacity;
};




int main()
{


	return 0;
}