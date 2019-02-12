#include <iostream>
#include "newSequence.h"
#include <cassert>
using namespace std;

void func(Sequence k) {}

int main()
{
	Sequence s;
	assert(s.empty());
	assert(s.find(9) == -1);
	assert(s.insert(99) == 0);
	assert(s.size() == 1 && s.find(99) == 0);
	assert(s.remove(9) == 0);
	assert(s.remove(99) == 1);
	assert(s.empty());
	for (int i = 0; i < 100; i++) {
		assert(s.insert(4) == 0);
	}
	for (int i = 100; i < 200; i++)
		assert(s.insert(1) == 0);
	s.remove(1);
	assert(s.size() == 100);
	s.remove(4);
	assert(s.empty());
	for (int i = 0; i < 200; i++) {
		assert(s.insert(i) == i);
	}
	assert(s.insert(0) == -1);
	assert(s.size() == 200);
	assert(!s.set(200, 200));
	assert(s.set(100, 100));
	unsigned long test[2];
	test[0] = 199;
	assert(!s.get(200, test[1]));
	assert(s.get(100, test[1]));
	assert(test[1] == 100);
	assert(s.find(test[1]) == 100);
	Sequence another(5);
	another.swap(s);
	assert(s.empty());
	assert(another.size() == 200);
	assert(another.find(test[0]) == (another.size() - 1));
	func(another);
	assert(another.find(test[0] - 1) == (another.size() - 2));
	Sequence assign_test(1000);
	assign_test = another;
	assert(assign_test.find(test[0] - 3) == (another.size() - 4));
	assert(assign_test.size() == 200 && assign_test.insert(1) == -1);
	for (int i = 0; i < 5; i++)
		assert(s.insert(0, 2));
	assert(!s.insert(0, 3));
	unsigned long temp;
	for (int i = 0; i < 5; i++)
		assert(s.get(i, temp) && temp == 2);
	assert(!s.get(5, temp));
	assert(s.size() == 5);
	s = s;
	assert(s.size() == 5 && s.get(3, temp) && temp == 2 && !s.get(5, temp) && !s.insert(0, 3));
	cout << "Passed all tests" << endl;
}