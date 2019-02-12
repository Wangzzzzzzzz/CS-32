#include "ScoreList.h"
#include "Sequence.h"

ScoreList::ScoreList() {}

bool ScoreList::add(unsigned long score) {
	if (score < 0 || score>100 || m_list.size() == 200)
		return false;
	m_list.insert(score);
	return true;
}

bool ScoreList::remove(unsigned long score) {
	return (m_list.erase(m_list.find(score)));
}

int ScoreList::size() const {
	return (m_list.size());
}

unsigned long ScoreList::minimum() const {
	if (m_list.empty())
		return NO_SCORE;
	unsigned long result;
	m_list.get(0, result);
	return result;
}

unsigned long ScoreList::maximum() const {
	if (m_list.empty())
		return NO_SCORE;
	unsigned long result;
	m_list.get(m_list.size() - 1, result);
	return result;
}