//
// Created by 22490 on 2023/5/27.
//

#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

namespace cjj
{
	class string
	{
	 public:

		// 迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _buffer;
		}
		iterator end()
		{
			return _buffer + _size;
		}
		const_iterator begin() const
		{
			return _buffer;
		}
		const_iterator end() const
		{
			return _buffer + _size;
		}

		// 构造
		string(const char* str = "")
			: _size(strlen(str))
		{
			_capacity = _size;
			_buffer = new char[_capacity + 1];
			strcpy(_buffer, str);
		}

		string(const string& s)
			: _size(s._size)
		{
			_capacity = _size;
			_buffer = new char[_capacity + 1];
			strcpy(_buffer, s._buffer);
		}

		string& operator=(const string& s)
		{
			if (this != &s)
			{
				// new失败抛异常的话，不会释放原有的
				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._buffer);

				delete[] _buffer;
				_buffer = tmp;

				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}

		// 运算符重载
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _buffer[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _buffer[pos];
		}
		bool operator>(const string& s) const
		{
			return strcmp(_buffer, s._buffer) > 0;
		}
		bool operator==(const string& s) const
		{
			return strcmp(_buffer, s._buffer) == 0;
		}
		bool operator<(const string& s) const
		{
			return !(*this > s || *this == s);
		}
		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}
		bool operator>=(const string& s) const
		{
			return !(*this < s);
		}
		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}
		string& operator+=(char ch)
		{
			insert(_size, ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			insert(_size, str);
			return *this;
		}

		// 成员函数
		size_t size() const
		{
			return _size;
		}

		const char* c_str() const
		{
			return _buffer;
		}

		void swap(string& s)
		{
			std::swap(_buffer, s._buffer);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _buffer);
				delete[] _buffer;
				_buffer = tmp;
				_capacity = n;
			}
		}

		void resize(size_t n, char ch = '\0')
		{
			if (n <= _size)
			{
				_size = n;
				_buffer[_size] = '\0';
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}

				for (size_t i = _size; i < n; i++)
					_buffer[i] = ch;

				_size = n;
				_buffer[_size] = '\0';
			}
		}

		void push_back(char ch)
		{
//			if (_size + 1 > _capacity)
//			{
//				reserve(_capacity * 2);
//			}
//			_buffer[_size] = ch;
//			_size++;
//			_buffer[_size] = '\0';
			insert(_size, ch);
		}

		void append(const char* str)
		{
//			size_t len = strlen(str);
//			if (_size + len > _capacity)
//			{
//				reserve(_size + len);
//			}
//			strcpy(_buffer + _size, str);
//			_size += len;
			insert(_size, str);
		}

		void insert(size_t pos, char ch)
		{
			assert(pos <= _size);
			if (_size + 1 > _capacity)
			{
				reserve(2 * _capacity);
			}

			size_t end = _size + 1;
			while (end > pos)
			{
				_buffer[end] = _buffer[end - 1];
				end--;
			}
			_buffer[pos] = ch;
			_size++;
		}

		void insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_capacity + len);
			}

			// 挪数据
			size_t end = _size + len + 1;
			while (end > pos)
			{
				_buffer[end] = _buffer[end - len];
				end--;
			}
			// 拷贝
			memmove(_buffer + pos, str, len);
			_size += len;
		}

		void erase(size_t pos, size_t n = npos)
		{
			if (n == npos || pos + n > _size)
			{
				_size = pos;
				_buffer[_size] = '\0';
			}
			else
			{
				memmove(_buffer + pos, _buffer + n + pos, _size - pos);
				_size -= n;
			}
		}

		const static size_t npos;

	 private:
		char* _buffer;
		size_t _size;
		size_t _capacity;
	};
	const size_t string::npos = -1;

	void test1()
	{
		string s1 = "abcd";
		for (int i = 0; i < s1.size(); i++)
			std::cout << s1[i];
		std::cout << std::endl;

		string s2(s1);
		for (int i = 0; i < s2.size(); i++)
			std::cout << s2[i];
		std::cout << std::endl;

		string s3 = s2;
		for (int i = 0; i < s3.size(); i++)
			std::cout << s3[i];
		std::cout << std::endl;

		const string s4 = "123";
		string s5 = s4;
		for (int i = 0; i < s5.size(); i++)
			std::cout << s5[i];
		std::cout << std::endl;
	}

	void test2()
	{
		string s1 = "abcd";
		for (auto ch : s1)
		{
			std::cout << ch;
		}
		std::cout << std::endl;
	}

	void test3()
	{
		string s1 = "";
		s1.append("abc");
		s1.append("123123123");
		s1.push_back('a');
		for (auto ch : s1)
		{
			std::cout << ch;
		}
		std::cout << std::endl;
	}

	void test4()
	{
		string s1;
		s1.resize(10, 'x');
		s1.resize(30, 'y');

		std::cout << s1.c_str() << std::endl;
		s1.resize(5);
		std::cout << s1.c_str() << std::endl;
		s1.insert(0, 'a');
		s1.insert(0, 'a');
		s1.insert(0, 'a');
		std::cout << s1.c_str() << std::endl;

		s1.insert(0, "RRR");

		std::cout << s1.c_str() << std::endl;

	}

	void test5()
	{
		string s = "xxxx";

		s += "123";
		std::cout << s.c_str() << std::endl;
		s.erase(2, 3);
		std::cout << s.c_str() << std::endl;
		s.erase(3, string::npos);
		std::cout << s.c_str() << std::endl;
		s.erase(1);
		std::cout << s.c_str() << std::endl;

	}
}