#include "Sequence.h"

Sequence::Sequence() {
	m_size = 0;
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
	if (pos < 0 || pos > m_size || m_size == DEFAULT_MAX_ITEMS)
		return false;
	seq_move(pos, m_size - 1, true);
	m_seq[pos] = value;
	++m_size;
	return true;
}

int Sequence::insert(const ItemType& value) {
	if (m_size == DEFAULT_MAX_ITEMS)
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
	int smallerSize = (m_size < other.m_size ? m_size : other.m_size);
	int temp_size;
	ItemType temp_element;
	//swap the overlapping part
	for (int i = 0; i < smallerSize; i++) {
		temp_element = m_seq[i];
		m_seq[i] = other.m_seq[i];
		other.m_seq[i] = temp_element;
	}

	//swap the remaining part
	if (m_size > smallerSize)
		for (int j = smallerSize; j < m_size; j++)
			other.m_seq[j] = m_seq[j];
	else if (other.m_size > smallerSize)
		for (int k = smallerSize; k < other.m_size; k++)
			m_seq[k] = other.m_seq[k];

	//sizes exchanged.
	temp_size = m_size;
	m_size = other.size();
	other.m_size = temp_size;
}