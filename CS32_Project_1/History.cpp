#include "History.h"
#include <iostream>

using namespace std;

//Constructor
History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	// Fill the grid with dots
	for (int r = 0; r < nRows; r++)
		for (int c = 0; c < nCols; c++)
			m_history[r][c] = '.';
}

void History::display() const{
	clearScreen();
	for (int r = 0; r < m_rows; r++) {
		for (int c = 0; c < m_cols; c++) {
			cout << m_history[r][c];
		}
		cout << endl;
	}	
	cout << endl;
}

bool History::record(int r, int c) {
	//out of range
	if (!isInBound(r, c))
		return false;
	
	//in the range, update the value
	char & hist = m_history[r - 1][c - 1];
	switch (hist) {
	case '.': hist = 'A'; break;
	case 'Z': break;
	default: hist++; break;
	}
	return true;
}

// checking if the range is satisfied
bool History::isInBound(int r, int c) {
	return (r >= 1 && r <= m_rows  &&  c >= 1 && c <= m_cols);
}
