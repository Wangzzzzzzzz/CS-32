#include "newSequence.h"
#include <cstdlib>
#include <iostream>

Sequence::Sequence() {
	m_size = 0;
	m_seq = new ItemType[DEFAULT_MAX_ITEMS];
	m_capacity = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int length) {
	if (length < 0) {
		std::cout << "Capacity " << length << " is not valid since it's less than 0"
			<< std::endl;
		std::exit(1);
	}
	m_size = 0;
	m_seq = new ItemType[length];
	m_capacity = length;
}

Sequence::~Sequence() {
	delete[] m_seq;
}

Sequence::Sequence(const Sequence& another_seq) {
	m_size = another_seq.m_size;
	m_capacity = another_seq.m_capacity;
	m_seq = new ItemType[m_capacity];
	for (int i = 0; i < m_size; i++)
		m_seq[i] = another_seq.m_seq[i];
}

Sequence& Sequence::operator = (const Sequence& another_seq) {
	if (this != &another_seq) {
		Sequence temp(another_seq);
		this->swap(temp);
	}
	return *this;
}

void Sequence::seq_move(int start, int end, bool back) {
	if (back) {
		for (int i = end; i >= start; i--)
			m_seq[i + 1] = m_seq[i];
	}
	if (!back) {
		for (int i = start; i <= end; i++)
			m_seq[i - 1] = m_seq[i];
	}
}

bool Sequence::empty() const {
	return (m_size == 0);
}

int Sequence::size() const {
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value) {
	if (pos < 0 || pos > m_size || m_size == m_capacity)
		return false;
	seq_move(pos, m_size - 1, true);
	m_seq[pos] = value;
	++m_size;
	return true;
}

int Sequence::insert(const ItemType& value) {
	if (m_size == m_capacity)
		return -1;
	int p = 0;
	while (value > m_seq[p] && p < m_size) {
		p++;
	}
	insert(p, value);
	return p;
}

bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= m_size)
		return false;
	seq_move(pos + 1, m_size - 1, false);
	--m_size;
	return true;
}

int Sequence::remove(const ItemType& value) {
	int size = 0;
	for (int i = 0; i < m_size; i++) {
		if (value != m_seq[i]) {
			m_seq[size] = m_seq[i];
			size++;
		}
	}
	int diff = m_size - size;
	m_size = size;
	return diff;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= m_size)
		return false;
	value = m_seq[pos];
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= m_size)
		return false;
	m_seq[pos] = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	int p = 0;
	while (m_seq[p] != value && p < m_size)
		p++;
	if (p == m_size)
		return -1;
	return p;
}

void Sequence::swap(Sequence& other) {
	//temp now gets the value or location of "this" Sequence 
	int temp_size = this->m_size;
	int temp_capacity = this->m_capacity;
	ItemType* temp_seq = this->m_seq;

	//"this" Sequence gets the value or location of other
	this->m_seq = other.m_seq;
	this->m_size = other.size();
	this->m_capacity = other.m_capacity;

	//other gets the value or location of temp (which is originally "this")
	other.m_seq = temp_seq;
	other.m_capacity = temp_capacity;
	other.m_size = temp_size;
}