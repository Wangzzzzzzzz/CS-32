void removeOdds(vector<int>& v)
{
	vector<int>::iterator p = v.begin();
	for (; p != v.end(); p++) {
		//find odd numbers
		if ((*p) % 2 != 0) {
			p = v.erase(p) - 1;
		}
	}
}