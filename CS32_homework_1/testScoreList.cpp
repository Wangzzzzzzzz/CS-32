#include "ScoreList.h"
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_func(ScoreList a){}

int main() {
	ScoreList test1;
	assert(test1.size() == 0);
	for (int i = 1; i <= 10; i++)
		assert(!test1.add(-10 * i));
	for (int i = 1; i <= 10; i++)
		assert(!test1.add(100 * i + 1));
	for (int i = 0; i < 10; i++)
		assert(test1.add(10 * i));
	unsigned long testlist[5] = { 100,100,90,99,56 };
	for (int i = 0; i < 5; i++)
		assert(test1.add(testlist[i]));
	assert(test1.size() == 15);
	assert(test1.remove(testlist[0]));
	assert(!test1.remove(-1) && !test1.remove(89));
	assert(test1.size() == 14);
	for (int i = 0; i < (200 - 14); i++)
		assert(test1.add(91));
	assert(test1.size() == 200);
	assert(!test1.add(90));
	assert(test1.maximum() == 100);
	assert(test1.minimum() == 0);
	ScoreList test2;
	assert(test2.maximum() == test2.minimum() && test2.maximum() == NO_SCORE);
	test_func(test1);
	assert(test1.maximum() == 100 && test1.size() == 200);
	cout << "Passed all test" << endl;
}
