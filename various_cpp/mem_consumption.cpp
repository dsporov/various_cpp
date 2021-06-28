#include <iostream>
#include <map>

namespace {
	class B {
		int a, b, c;
	};

	class A {
	public:
		int n;
		double d;
		std::map<int, B> m;
	};
}

void test_mem_consumption() {
	A a;
	a.m[1] = B();

	std::cout << sizeof(A) << "\n";
}