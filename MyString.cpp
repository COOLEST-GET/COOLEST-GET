#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>


class MyString
{

	// 输入输出重载
    friend ostream& operator<<(ostream& os, const MyString& s)  
    {  
        os << s._str;  
        return os;  
    }

	friend istream& operator>>(istream& in, MyString& s)
	{
		s.clear();
		char buffer[128];
		in >> buffer;
		s += buffer;
		return in;
	}

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
			_str = tmp;
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
		assert(pos < _size);
		return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _str[pos];
	}

	char& front()
	{
		assert(_size > 0);
		return _str[0];
	}

	const char& front() const
	{
		assert(_size > 0);
		return _str[0];
	}

	char& back()
	{
		assert(_size > 0);
		return _str[_size - 1];
	}

	const char& back() const
	{
		assert(_size > 0);
		return _str[_size - 1];
	}

	const char* c_str() const
	{
		return _str;
	}

	// 修改操作
	void push_back(char ch)
	{
		if (_size >= _capacity)
		{
			reserve(_capacity * 2);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	MyString& append(const char* str)
	{
		if (!str) 
		{
			return *this;
		}

		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}

		strcpy(_str + _size, str);
		_size += len;
	}

	MyString& push_back(const char* str)
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

		for (size_t i = _size + 1; i > pos; --i)
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

		strncpy(_str + pos, str, len);
		_size += len;
		_str[_size] = '\0';
		return *this;
	}

	MyString& erase(size_t pos, size_t len = size_t(-1))
	{
		assert(pos < _size);
		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}
		return *this;
	}

	void swap(MyString& s)
	{
		using std::swap;
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	// 查找操作
	size_t find(char ch, size_t pos = 0)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; ++i)
		{
			if (_str[i] == ch)
				return i;
		}
		return size_t(-1);
	}

	size_t find(const char* str, size_t pos = 0)
	{
		assert(pos < _size);
		const char* p = strstr(_str + pos, str);
		return p ? (p - _str) : size_t(-1);
	}

	size_t find(const MyString& s, size_t pos = 0)
	{
		assert(pos < _size);
		return find(s._str, pos);
	}

	// 运算符重载
	MyString& operator=(const MyString& s)
	{
		if(this != &s)
		{
			char* tmp = new char[s._capacity + 1];
			strcpy(tmp, s._str);
			delete[] _str;
			_str = tmp;
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}

	MyString& operator=(MyString&& s) noexcept
	{
		if (this != &s)
		{
			delete[] _str;
			_str = s._str;
			_size = s._size;
			_capacity = s._capacity;
			s._str = nullptr;
			s._size = s._capacity = 0;
		}
		return *this;
	}

	MyString& operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	MyString& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	MyString& operator+=(const MyString& s)
	{
		append(s._str);
		return *this;
	}

	bool operator==(const MyString& s) const { return strcmp(_str, s._str) == 0; }
	bool operator!=(const MyString& s) const { return !(*this == s); }
	bool operator>(const MyString& s) const { return strcmp(_str, s._str) > 0; }
	bool operator<(const MyString& s) const { return strcmp(_str, s._str) < 0; }
	bool operator>=(const MyString& s) const { return !(*this < s); }
	bool operator<=(const MyString& s) const { return !(*this > s); }



private:
	char* _str;
	size_t _size;
	size_t _capacity;
};



int main()
{
	cout << "=== 构造与输出测试 ===" << endl;
	MyString s1("Hello");
	cout << "s1: " << s1 << endl;

	MyString s2;              // 默认构造
	cout << "s2 (default): " << s2 << endl;

	MyString s3 = s1;         // 拷贝构造
	cout << "s3 (copy of s1): " << s3 << endl;

	MyString s4 = MyString("World"); // 移动构造
	cout << "s4 (move): " << s4 << endl;

	cout << "\n=== push_back & append ===" << endl;
	s1.push_back('!');
	cout << "s1 after push_back('!'): " << s1 << endl;

	s1.append(" Nice to meet you.");
	cout << "s1 after append: " << s1 << endl;

	s1.push_back(" Let's code.");
	cout << "s1 after push_back(c-string): " << s1 << endl;

	cout << "\n=== insert ===" << endl;
	s1.insert(6, 'X');
	cout << "s1 after insert(6, 'X'): " << s1 << endl;

	s1.insert(0, "Start-");
	cout << "s1 after insert(0, \"Start-\"): " << s1 << endl;

	cout << "\n=== erase ===" << endl;
	s1.erase(0, 6);
	cout << "s1 after erase(0,6): " << s1 << endl;

	s1.erase(s1.size() - 1);  // 删除最后一个字符
	cout << "s1 after erase last char: " << s1 << endl;

	cout << "\n=== resize & clear ===" << endl;
	s1.resize(5);
	cout << "s1 after resize(5): " << s1 << endl;

	s1.resize(10, '*');
	cout << "s1 after resize(10, '*'): " << s1 << endl;

	s1.clear();
	cout << "s1 after clear(): " << s1 << " (empty? " << boolalpha << s1.empty() << ")" << endl;

	cout << "\n=== swap ===" << endl;
	MyString a("AAA"), b("BBB");
	cout << "Before swap: a=" << a << ", b=" << b << endl;
	a.swap(b);
	cout << "After swap: a=" << a << ", b=" << b << endl;

	cout << "\n=== front/back/operator[] ===" << endl;
	MyString s5("ABCDE");
	cout << "s5: " << s5 << ", front=" << s5.front() << ", back=" << s5.back() << endl;
	s5[0] = 'Z';
	s5[4] = 'Y';
	cout << "s5 after modifying: " << s5 << endl;

	cout << "\n=== find ===" << endl;
	size_t pos1 = s5.find('D');
	size_t pos2 = s5.find("BC");
	cout << "Find 'D': " << pos1 << ", Find \"BC\": " << pos2 << endl;

	cout << "\n=== operator+= and assignment ===" << endl;
	MyString s6("Hello");
	s6 += ',';
	s6 += " world";
	MyString s7;
	s7 = s6;
	cout << "s6 after +=: " << s6 << ", s7 after assignment: " << s7 << endl;

	cout << "\n=== comparison operators ===" << endl;
	MyString x("abc"), y("xyz");
	cout << "x=" << x << ", y=" << y << endl;
	cout << "x==y? " << (x == y) << ", x!=y? " << (x != y) << endl;
	cout << "x>y? " << (x > y) << ", x<y? " << (x < y) << endl;
	cout << "x>=y? " << (x >= y) << ", x<=y? " << (x <= y) << endl;

	cout << "\n=== iterators ===" << endl;
	cout << "s5 chars: ";
	for (auto it = s5.begin(); it != s5.end(); ++it)
		cout << *it << ' ';
	cout << endl;

	cout << "\n=== istream >> operator ===" << endl;
	MyString inputStr;
	cout << "Enter a word: ";
	cin >> inputStr;
	cout << "You entered: " << inputStr << endl;

	return 0;
}