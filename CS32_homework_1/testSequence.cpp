#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence s;
	assert(s.empty());
	assert(s.find(1) == -1);
	assert(s.insert(1) == 0);
	assert(s.size() == 1 && s.find(1) == 0);
	assert(s.remove(9) == 0);
	assert(s.remove(1) == 1);
	assert(s.empty());
	for (int i = 0; i < 100; i++) {
		assert(s.insert(1) == 0);
	}
	for (int i = 100; i < 200; i++)
		assert(s.insert(2) == 100);
	s.remove(1);
	assert(s.size() == 100);
	s.remove(2);
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
	Sequence another;
	another.swap(s);
	assert(s.empty());
	assert(another.size() == 200);
	assert(another.find(test[0]) == (another.size() - 1));
	cout << "Passed all tests" << endl;
}