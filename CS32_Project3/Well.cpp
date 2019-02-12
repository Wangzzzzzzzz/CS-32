#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <stack>
#include <iostream>
#include <cstdlib>

/*Class Layer*/
Well::Layer::Layer(bool isBottom, int layer_width)
	:boundary('@'), m_isBottom(isBottom), m_isFull(false), m_filled(0),m_layer_width(layer_width)
{
	if (layer_width <= 0) {
		std::cerr << "Layer must contain at least one element";
		exit(1);
	}
	if (isBottom) {
		for (int i = 0; i < layer_width; i++)
			m_array.push_back('@');
	}
	else {
		for (int i = 0; i < layer_width; i++)
			m_array.push_back(' ');
	}
}



//can only be used when other functions has confirmed that writing is valid
void Well::Layer::write(int start_pos, const std::string reference, int length) {
	if (length < 0 || length > reference.length() || length >= m_layer_width)
		return;
	int pos = 0;
	//identify the first spot not a ' '
	while (pos < length && reference[pos] == ' ')
		pos++;
	//there is no need to write anything
	if (pos == length)
		return;
	else {
		for(;pos < length; pos++)
			if (reference[pos] != ' ' && start_pos + pos < m_layer_width) {
				this->m_array[start_pos + pos] = reference[pos];
			}
	}
}

void Well::Layer::clear(int start_pos, int length) {
	if (length < 0 || length >= m_layer_width)
		return;
	//ensure to access element after position 0
	int pos = (start_pos < 0 ? 0 - start_pos : 0);
	for (; pos < length && start_pos + pos < m_layer_width; pos++) {
		if (this->m_array[start_pos + pos] == '#') {
			m_array[start_pos + pos] = ' ';
		}
	}
}

int Well::Layer::mutate(char org, char after) {
	int count = 0;
	for (int pos = 0; pos < this->m_layer_width; pos++) {
		if (m_array[pos] == org) {
			m_array[pos] = after;
			count++;
		}
	}
	return count;
}

std::string Well::Layer::display() const {
	std::string result;
	result = boundary + m_array + boundary;
	return result;
}

bool Well::Layer::empty() {
	if (m_isFull) {
		for (int pos = 0; pos < m_layer_width; pos++)
			m_array[pos] = ' ';
		m_isFull = false;
		m_filled = 0;
		return true;
	}
	return false;
}

void Well::Layer::destroy() {
	for (int pos = 0; pos < m_layer_width; pos++)
		m_array[pos] = ' ';
	m_isFull = false;
	m_filled = 0;
}

char Well::Layer::getElement(int postition) const {
	if (postition < 0 || postition > m_layer_width)
		return '\0';
	return m_array[postition];
}

void Well::Layer::updateFullness(int newFixed) {
	if (newFixed < 0)
		m_filled = (m_filled + newFixed < 0 ? 0 : m_filled + newFixed);
	else
		m_filled = (m_filled + newFixed > m_layer_width ? m_layer_width : m_filled + newFixed);
	if (m_filled == m_layer_width)
		m_isFull = true;
}
/*End of Layer*/

/*Class Well*/
Well::Well(int well_depth, int well_width) 
	:m_depth(well_depth),m_width(well_width),curPiece(nullptr)
{
	if (well_depth <= 0 || well_width <= 0) {
		std::cerr << "Well cannot be initialized with size " << well_depth << " * " << well_width;
		exit(1);
	}
	m_bottom = new Layer(true, well_width);
	m_layer = new Layer*[well_depth];
	for (int layerIndex = 0; layerIndex < well_depth; layerIndex++) {
		m_layer[layerIndex] = new Layer(false, well_width);
	}
}

Well::~Well() {
	delete m_bottom;
	for (int layerIndex = 0; layerIndex < m_depth; layerIndex++) {
		delete m_layer[layerIndex];
	}
	delete[] m_layer;
	delete curPiece;
}

void Well::updatePiece(Piece* another) {
	if (another != this->curPiece)
		curPiece = another;
}

bool Well::addPiece() {
	bool test = attemptOverWrite(3, 0, curPiece->get_graph());
	for (int i = 0; i < 4; i++)
		m_layer[i]->write(3, curPiece->get_graph()[i], 4);
	return test;
}

bool Well::canGoDown() const{
	int x = curPiece->getX();
	int y = curPiece->getY();
	bool column[4];
	for (int i = 0; i < 4; i++) {
		int k;
		//get first element not ' '
		for (k = 3; k > -1 && curPiece->get_graph()[k][i] == ' '; k--);
		if (k == -1)
			column[i] = true;
		else if (k + y + 1 >= m_depth)	//if reached the end of the well
			column[i] = false;
		else if (m_layer[k + y + 1]->getElement(x + i) == ' ')	//if i th column can move down
			column[i] = true;
		else
			column[i] = false;
	}
	return (column[0] && column[1] && column[2] && column[3]);
}

bool Well::canGoRight() const {
	//at the boundary
	if ((curPiece->rightmost() + curPiece->getX()) >= (m_width - 1))
		return false;
	//general case
	int x = curPiece->getX();
	int y = curPiece->getY();
	bool row[4];
	for (int i = 0; i < 4; i++) {
		int k;
		for (k = 3; k > -1 && curPiece->get_graph()[i][k] == ' '; k--);	//the right most # for each row
		//a blank row
		if (k == -1)
			row[i] = true;
		//a non blank row is always in range, x+k+1 is valid when piece is not at boundary
		else if (m_layer[y + i]->getElement(x + k + 1) == ' ')
			row[i] = true;
		else
			row[i] = false;
	}
	return (row[0] && row[1] && row[2] && row[3]);
}

bool Well::canGoLeft() const {
	//at the boundary
	if ((curPiece->leftmost() + curPiece->getX()) <= 0)
		return false;
	//general case
	int x = curPiece->getX();
	int y = curPiece->getY();
	bool row[4];
	for (int i = 0; i < 4; i++) {
		int k;
		for (k = 0; k < 4 && curPiece->get_graph()[i][k] == ' '; k++);
		if (k == 4)
			row[i] = true;
		else if (m_layer[y + i]->getElement(x + k - 1) == ' ')
			row[i] = true;
		else
			row[i] = false;
	}
	return (row[0] && row[1] && row[2] && row[3]);
}

bool Well::attemptOverWrite(int x, int y, const char graph[4][4]) const {
	bool result = true;
	bool temp;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			if (graph[i][k] != ' ') {
				if (y + i >= m_depth || x + k < 0 || x + k >= m_width)
					return false;
				temp = (m_layer[y + i]->getElement(x + k) == ' ');
				result = (temp && result);
			}
			if (!result)
				return false;
		}
	}
	return true;
}

bool Well::attemptOverWrite(int x, int y, const std::string* graph) const {
	bool result = true;
	bool temp;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			if (graph[i][k] != ' ') {
				if (y + i >= m_depth || x + k < 0 || x + k >= m_width)
					return false;
				temp = (m_layer[y + i]->getElement(x + k) == ' ');
				result = (temp && result);
			}
			if (!result)
				return false;
		}
	}
	return true;
}

bool Well::canRotate() const {
	char temp[4][4];
	switch (curPiece->pieceKind()) {
	case PIECE_I:
		if (curPiece->get_next_ori() == 0 || curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_02_PIECE_I, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_13_PIECE_I, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_J:
		if (curPiece->get_next_ori() == 0) {
			pieceWrite(_ORT_0_PIECE_J, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 1) {
			pieceWrite(_ORT_1_PIECE_J, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_2_PIECE_J, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_3_PIECE_J, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_L:
		if (curPiece->get_next_ori() == 0) {
			pieceWrite(_ORT_0_PIECE_L, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 1) {
			pieceWrite(_ORT_1_PIECE_L, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_2_PIECE_L, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_3_PIECE_L, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_T:
		if (curPiece->get_next_ori() == 0) {
			pieceWrite(_ORT_0_PIECE_T, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 1) {
			pieceWrite(_ORT_1_PIECE_T, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_2_PIECE_T, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_3_PIECE_T, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_S:
		if (curPiece->get_next_ori() == 0 || curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_02_PIECE_S, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_13_PIECE_S, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_Z:
		if (curPiece->get_next_ori() == 0 || curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_02_PIECE_Z, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_13_PIECE_Z, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_CRAZY:
		if (curPiece->get_next_ori() == 0) {
			pieceWrite(_ORT_0_PIECE_CRAZY, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 1) {
			pieceWrite(_ORT_1_PIECE_CRAZY, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else if (curPiece->get_next_ori() == 2) {
			pieceWrite(_ORT_2_PIECE_CRAZY, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
		else {
			pieceWrite(_ORT_3_PIECE_CRAZY, temp);
			return attemptOverWrite(curPiece->getX(), curPiece->getY(), temp);
		}
	case PIECE_VAPOR:
	case PIECE_FOAM:
	case PIECE_O:
		return true;
	default:
		return false;
	}
}

void Well::FoamWrite(int cur_x, int cur_y, const int bomb_x, const int bomb_y) {
	m_layer[cur_y]->m_array[cur_x] = '*';
	m_layer[cur_y]->updateFullness(1);

	//go down
	if (cur_y + 1 < m_depth && cur_y + 1 <= bomb_y + 2
		&& m_layer[cur_y + 1]->getElement(cur_x) == ' ')
	{
		FoamWrite(cur_x, cur_y + 1, bomb_x, bomb_y);
	}
	//go up
	if (cur_y - 1 >= 0 && cur_y - 1 >= bomb_y - 2
		&& m_layer[cur_y - 1]->getElement(cur_x) == ' ')
	{
		FoamWrite(cur_x, cur_y - 1, bomb_x, bomb_y);
	}
	//go left
	if (cur_x - 1 >= 0 && cur_x - 1 >= bomb_x - 2
		&& m_layer[cur_y]->getElement(cur_x - 1) == ' ')
	{
		FoamWrite(cur_x - 1, cur_y, bomb_x, bomb_y);
	}
	//go right
	if (cur_x + 1 < m_width && cur_x + 1 <= bomb_x + 2
		&& m_layer[cur_y]->getElement(cur_x + 1) == ' ')
	{
		FoamWrite(cur_x + 1, cur_y, bomb_x, bomb_y);
	}
}

//fix a piece also update how much is fixed and if a row is full
void Well::fix(){
	switch (curPiece->pieceKind()) {
	case PIECE_CRAZY:
	case PIECE_I:
	case PIECE_J:
	case PIECE_L:
	case PIECE_O:
	case PIECE_S:
	case PIECE_T:
	case PIECE_Z:
	{
		int temp;
		for (int i = curPiece->getY(); i < curPiece->getY() + 4 && i < m_depth; i++) {
			temp = m_layer[i]->mutate('#', '$');
			m_layer[i]->updateFullness(temp);
		}
		break;
	}
	case PIECE_FOAM:
	{
		int bomb_x = curPiece->getX() + 1;
		int bomb_y = curPiece->getY() + 1;
		FoamWrite(bomb_x, bomb_y, bomb_x, bomb_y);
		break;
	}
	case PIECE_VAPOR:
	{
		int count;
		int bomb_x = curPiece->getX() + 1;
		int bomb_y = curPiece->getY();
		int vapor_start = (bomb_y - 2 < 0 ? 0 : bomb_y - 2);
		int vapor_end = (bomb_y + 2 >= m_depth ? (m_depth-1) : bomb_y + 2);
		for (int i = vapor_start; i <= vapor_end; i++) {
			count = 0;
			if (i == bomb_y) {
				m_layer[i]->m_array[bomb_x] = ' ';
				m_layer[i]->m_array[bomb_x + 1] = ' ';
				continue;
			}
			if (m_layer[i]->m_array[bomb_x] != ' ') {
				count--;
				m_layer[i]->m_array[bomb_x] = ' ';
			}
			if (m_layer[i]->m_array[bomb_x + 1] != ' ') {
				count--;
				m_layer[i]->m_array[bomb_x + 1] = ' ';
			}
			m_layer[i]->updateFullness(count);
		}
		break;
	}
	default:
		break;
	}
	delete curPiece;
}

bool Well::moveDown() {
	if (!this->canGoDown())
		return false;
	clearPiece();
	curPiece->move_down();
	writePiece(curPiece->getX(), curPiece->getY());
	return true;
}

void Well::moveRight() {
	if (curPiece->pieceKind() == PIECE_CRAZY) {
		if (!this->canGoLeft())
			return;
	}
	else if (!this->canGoRight())
		return;
	clearPiece();
	curPiece->move_right();
	writePiece(curPiece->getX(), curPiece->getY());
}

void Well::moveLeft() {
	if (curPiece->pieceKind() == PIECE_CRAZY) {
		if (!this->canGoRight())
			return;
	}
	else if (!this->canGoLeft())
			return;
	clearPiece();
	curPiece->move_left();
	writePiece(curPiece->getX(), curPiece->getY());
}

void Well::rotate() {
	clearPiece();
	if (!this->canRotate()) {
		writePiece(curPiece->getX(), curPiece->getY());
		return;
	}
	curPiece->rotate();
	writePiece(curPiece->getX(), curPiece->getY());
}

int Well::clean() {
	Layer** temp = new Layer*[m_depth];
	int count = 0;
	int k = m_depth - 1;
	for (int i = m_depth-1; i >=0 ;i--) {
		if (m_layer[i]->empty()) {
			temp[count] = m_layer[i];
			count++;
		}
		else {
			temp[k] = m_layer[i];
			k--;
		}
	}
	delete[] m_layer;
	m_layer = temp;
	return count;
}

void Well::discard() {
	for (int i = m_depth - 1; i >= 0; i--) {
		m_layer[i]->destroy();
	}
}

void Well::writePiece(int x, int y) {
	for (int i = 0; i < 4  && y+i < m_depth; i++) {
		m_layer[y + i]->write(x, curPiece->get_graph()[i], 4);
	}
}

void Well::clearPiece() {
	int x = curPiece->getX();
	int y = curPiece->getY();
	for (int i = 0; i < 4 && y + i < m_depth; i++) {
		m_layer[y + i]->clear(x, 4);
	}
}

void Well::display(Screen& screen, int x, int y)
{
	for (int i = 0; i < m_depth; i++) {
		screen.gotoXY(x, y + i);
		screen.printString(m_layer[i]->display());
	}
	screen.gotoXY(x, y + m_depth);
	screen.printString(m_bottom->display());
	screen.refresh();
}
