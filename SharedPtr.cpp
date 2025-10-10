#include <iostream>
#include <string>
using namespace std;

template <typename T>
class SharedPtr {
private:
	T* ptr;
	size_t* count;

	void release() {
		if (count) {
			if (--(*count) == 0) {
				delete ptr;
				delete count;
			}
			ptr = nullptr;
			count = nullptr;
		}
	}

public:
	SharedPtr() : ptr(nullptr), count(nullptr){}

	explicit SharedPtr(T* p) : ptr(p), count(new size_t(1)){}

	SharedPtr(const SharedPtr& other) : ptr(other.ptr), count(other.count) {
		if (count) { ++(*count); }
	}

	SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), count(other.count) {
		other.ptr = nullptr;
		other.count = nullptr;
	}

	SharedPtr& operator=(const SharedPtr& other) {
		if (this == &other) { return *this; }

		release();
		ptr = other.ptr;
		count = other.count;

		if (count) { ++(*count); }
		return *this;
	}

	SharedPtr& operator=(SharedPtr&& other) noexcept {
		if (this == &other) { return *this; }

		release();
		ptr = other.ptr;
		count = other.count;
		other.ptr = nullptr;
		other.count = nullptr;
		return *this;
	}

	~SharedPtr() {
		release();
	}

	size_t use_count() const {
		return count ? *count : 0;
	}

	T* get() const {
		return ptr;
	}

	T& operator*() const {
		return *ptr;
	}

	T* operator->() const {
		return ptr;
	}

	void reset(T* p = nullptr) {
		release();
		if (p) {
			ptr = p;
			count = new size_t(1);
		}
	}

	bool unique() const {
		return use_count() == 1;
	}

	explicit operator bool() const {
		return ptr != nullptr;
	}
};

struct demo
{
	string name;

	demo(string n) : name(move(n)) {
		cout << "demo Construct" << name << endl;
	}

	~demo() {
		cout << "demo Destruct" << name << endl;
	}

	void hello() const {
		cout << "hello i'm " << name << endl;
	}
};

int main() {
	cout << "=== 构造与拷贝/移动测试 ===" << endl;
	SharedPtr<demo> p1(new demo("A"));
	cout << "p1.use_count() = " << p1.use_count() << endl;

	SharedPtr<demo> p2 = p1; // 拷贝构造
	cout << "p1.use_count() = " << p1.use_count() << ", p2.use_count() = " << p2.use_count() << endl;

	SharedPtr<demo> p3;
	p3 = p1; // 拷贝赋值
	cout << "p1.use_count() = " << p1.use_count() << ", p3.use_count() = " << p3.use_count() << endl;

	SharedPtr<demo> p4 = move(p2); // 移动构造
	cout << "p2 是否为空？" << (p2 ? "否" : "是") << endl;

	SharedPtr<demo> p5;
	p5 = move(p3); // 移动赋值
	cout << "p3 是否为空？" << (p3 ? "否" : "是") << endl;

	cout << "\n=== operator* / operator-> / get / unique 测试 ===" << endl;
	(*p1).hello();        // operator*
	p4->hello();           // operator->
	cout << "p1.get() = " << p1.get() << endl; // get()
	cout << "p1 是否唯一？" << (p1.unique() ? "是" : "否") << endl;

	cout << "\n=== reset 测试 ===" << endl;
	p1.reset(new demo("B"));
	cout << "p1.use_count() = " << p1.use_count() << endl;
	p1->hello();

	cout << "\n=== scope exit 测试 ===" << endl;
	return 0;
}