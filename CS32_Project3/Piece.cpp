#include "Piece.h"

void pieceWrite(const char ref[4][4], char obj[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			obj[i][k] = ref[i][k];
		}
	}
}


void blockWrite(const char ref[4][4], std::string* obj) {
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			obj[i][k] = ref[i][k];
		}
	}
}

/*Base Class*/
Piece::Piece(PieceType chosen, Well* wl, const char ref[4][4])
	:m_piece(chosen), m_pos_x(3), m_pos_y(0), m_well(wl), block(new std::string[4]),orientation(0)
{
	for (int i = 0; i < 4; i++) {
		block[i] = "    ";
	}
	blockWrite(ref, block);
}

Piece::~Piece()
{
	delete[] block;
}

void Piece::move_down() {
	m_pos_y++;
}

PieceType Piece::pieceKind() const{
	return m_piece;
}

int Piece::getX() const {
	return m_pos_x;
}

int Piece::getY() const {
	return m_pos_y;
}

void Piece::move_right() {
	m_pos_x++;
}

void Piece::move_left() {
	m_pos_x--;
}

std::string* Piece::get_graph() const {
	return block;
}

int Piece::get_orientation() const {
	return orientation;
}

void Piece::update_orientation() {
	switch (orientation) {
	case 0:
		orientation = 1;
		break;
	case 1:
		orientation = 2;
		break;
	case 2:
		orientation = 3;
		break;
	case 3:
		orientation = 0;
		break;
	default:
		break;
	}
}

int Piece::get_next_ori() const {
	switch (orientation) {
	case 0:
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 0;
	default:
		return -1;
	}
}

void Piece::change_graph_to(const char ref[4][4]) {
	blockWrite(ref, block);
}
/*End of Base*/

/*Piece I*/
PieceI::PieceI(Well* well) 
	:Piece(PIECE_I,well,_ORT_02_PIECE_I)
{
}

void PieceI::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_I);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_I);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_I);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_I);
		break;
	default:
		break;
	}
}

int PieceI::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 0;
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}

int PieceI::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 3;
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}
/*End of Piece I*/

/*Piece L*/
PieceL::PieceL(Well* well)
	:Piece(PIECE_L, well,_ORT_0_PIECE_L)
{
}

void PieceL::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_1_PIECE_L);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_2_PIECE_L);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_3_PIECE_L);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_0_PIECE_L);
		break;
	default:
		break;
	}
}

int PieceL::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 0;
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}

int PieceL::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 1:
	case 3:
		return 2;
	default:
		return -1;
	}
}
/*End of Piece L*/

/*Piece J*/
PieceJ::PieceJ(Well* well)
	:Piece(PIECE_J, well, _ORT_0_PIECE_J)
{
}

void PieceJ::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_1_PIECE_J);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_2_PIECE_J);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_3_PIECE_J);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_0_PIECE_J);
		break;
	default:
		break;
	}
}

int PieceJ::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}

int PieceJ::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 3;
	case 1:
	case 3:
		return 2;
	default:
		return -1;
	}
}
/*End of Piece J*/

/*Piece T*/
PieceT::PieceT(Well* well)
	:Piece(PIECE_T, well,_ORT_0_PIECE_T)
{
}


void PieceT::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_1_PIECE_T);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_2_PIECE_T);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_3_PIECE_T);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_0_PIECE_T);
		break;
	default:
		break;
	}
}

int PieceT::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 3:
		return 0;
	case 1:
		return 1;
	default:
		return -1;
	}
}

int PieceT::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 1:
	case 2:
		return 2;
	case 3:
		return 1;
	default:
		return -1;
	}
}
/*End of Piece T*/

/*Piece O*/
PieceO::PieceO(Well* well)
	:Piece(PIECE_O, well,_ORT_0123_PIECE_O)
{
}

void PieceO::rotate() {
	update_orientation();
	return;
}

int PieceO::leftmost() const {
	return 0;
}

int PieceO::rightmost() const {
	return 1;
}
/*End of Piece O*/

/*Piece S*/
PieceS::PieceS(Well* well)
	:Piece(PIECE_S, well, _ORT_02_PIECE_S)
{
}

void PieceS::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_S);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_S);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_S);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_S);
		break;
	default:
		break;
	}
}

int PieceS::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 0;
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}

int PieceS::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 1:
	case 3:
		return 2;
	default:
		return -1;
	}
}
/*End of Piece S*/

/*Piece Z*/
PieceZ::PieceZ(Well* well)
	:Piece(PIECE_Z, well,_ORT_02_PIECE_Z)
{
}

void PieceZ::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_Z);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_Z);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_13_PIECE_Z);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_02_PIECE_Z);
		break;
	default:
		break;
	}
}

int PieceZ::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
		return 0;
	case 1:
	case 3:
		return 1;
	default:
		return -1;
	}
}

int PieceZ::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 1:
	case 3:
		return 2;
	default:
		return -1;
	}
}
/*End of Piece Z*/

/*Piece Vapor Bomb*/
PieceVapor::PieceVapor(Well* well)
	:Piece(PIECE_VAPOR, well,_ORT_0123_PIECE_VAPOR)
{
}

void PieceVapor::rotate() {
	update_orientation();
	return;
}

int PieceVapor::leftmost() const {
	return 1;
}

int PieceVapor::rightmost() const {
	return 2;
}
/*End of Piece Vapor Bomb*/

/*Piece Foam Bomb*/
PieceFoam::PieceFoam(Well* well)
	:Piece(PIECE_FOAM, well, _ORT_0123_PIECE_FOAM)
{
}

void PieceFoam::rotate() {
	update_orientation();
	return;
}

int PieceFoam::leftmost() const {
	return 1;
}

int PieceFoam::rightmost() const {
	return 1;
}
/*End of Piece Foam Bomb*/

/*Piece Crazy*/
PieceCrazy::PieceCrazy(Well* well)
	:Piece(PIECE_CRAZY, well,_ORT_0_PIECE_CRAZY)
{
}

void PieceCrazy::rotate() {
	switch (this->get_orientation())
	{
	case 0:
		update_orientation();
		change_graph_to(_ORT_1_PIECE_CRAZY);
		break;
	case 1:
		update_orientation();
		change_graph_to(_ORT_2_PIECE_CRAZY);
		break;
	case 2:
		update_orientation();
		change_graph_to(_ORT_3_PIECE_CRAZY);
		break;
	case 3:
		update_orientation();
		change_graph_to(_ORT_0_PIECE_CRAZY);
		break;
	default:
		break;
	}
}

void PieceCrazy::move_left() {
	Piece::move_right();
}

void PieceCrazy::move_right() {
	Piece::move_left();
}

int PieceCrazy::leftmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 2:
	case 3:
		return 0;
	case 1:
		return 2;
	default:
		return -1;
	}
}

int PieceCrazy::rightmost() const {
	switch (this->get_orientation()) {
	case 0:
	case 1:
	case 2:
		return 3;
	case 3:
		return 1;
	default:
		return -1;
	}
}
/*End of Crazy Piece*/