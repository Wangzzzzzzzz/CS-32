#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include <string>
class Well;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

//piece I orientation 0 and 2
const char _ORT_02_PIECE_I[4][4] =
{	{ ' ',' ',' ',' '},
	{ '#','#','#','#'},
	{ ' ',' ',' ',' '},
	{ ' ',' ',' ',' '} };

//piece I orientation 1 and 3
const char _ORT_13_PIECE_I[4][4] =
{	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' } };

//piece L oritentation 0
const char _ORT_0_PIECE_L[4][4] =
{	{ ' ',' ',' ',' ' },
	{ '#','#','#',' ' },
	{ '#',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece L oritentation 1
const char _ORT_1_PIECE_L[4][4] =
{	{ ' ','#','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ',' ',' ' } };

//piece L oritentation 2
const char _ORT_2_PIECE_L[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ',' ','#',' ' },
	{ '#','#','#',' ' },
	{ ' ',' ',' ',' ' } };

//piece L oritentation 3
const char _ORT_3_PIECE_L[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' '},
	{ ' ','#',' ',' '},
	{ ' ','#','#',' '} };

//piece J oritentation 0
const char _ORT_0_PIECE_J[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ','#','#','#' },
	{ ' ',' ',' ','#' },
	{ ' ',' ',' ',' ' } };

//piece J oritentation 1
const char _ORT_1_PIECE_J[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ','#','#',' ' } };

//piece J oritentation 2
const char _ORT_2_PIECE_J[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#','#','#' },
	{ ' ',' ',' ',' ' } };

//piece J oritentation 3
const char _ORT_3_PIECE_J[4][4] =
{	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece T oritentation 0
const char _ORT_0_PIECE_T[4][4] =
{	{ ' ','#',' ',' ' },
	{ '#','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece T oritentation 1
const char _ORT_1_PIECE_T[4][4] =
{	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece T oritentation 2
const char _ORT_2_PIECE_T[4][4] =
{	{ ' ',' ',' ',' ' },
	{ '#','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece T oritentation 3
const char _ORT_3_PIECE_T[4][4] =
{	{ ' ','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece S oritentation 0,2
const char _ORT_02_PIECE_S[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ','#','#',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece S oritentation 1,3
const char _ORT_13_PIECE_S[4][4] =
{	{ ' ','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ',' ',' ' } };

//piece Z oritentation 0,2
const char _ORT_02_PIECE_Z[4][4] =
{	{ ' ',' ',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' } };

//piece Z oritentation 1,3
const char _ORT_13_PIECE_Z[4][4] =
{	{ ' ',' ','#',' ' },
	{ ' ','#','#',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece O oritentation 0123
const char _ORT_0123_PIECE_O[4][4] =
{	{ '#','#',' ',' ' },
	{ '#','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece VaporBomb oritentation 0123
const char _ORT_0123_PIECE_VAPOR[4][4] =
{	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece FoamBomb oritentation 0123
const char _ORT_0123_PIECE_FOAM[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece CrazyShape oritentation 0
const char _ORT_0_PIECE_CRAZY[4][4] =
{	{ '#',' ',' ','#' },
	{ ' ','#','#',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' } };

//piece CrazyShape oritentation 1
const char _ORT_1_PIECE_CRAZY[4][4] =
{	{ ' ',' ',' ','#' },
	{ ' ',' ','#',' ' },
	{ ' ',' ','#',' ' },
	{ ' ',' ',' ','#' } };

//piece CrazyShape oritentation 2
const char _ORT_2_PIECE_CRAZY[4][4] =
{	{ ' ',' ',' ',' ' },
	{ ' ',' ',' ',' ' },
	{ ' ','#','#',' ' },
	{ '#',' ',' ','#' } };

//piece Crazy oritentation 3
const char _ORT_3_PIECE_CRAZY[4][4] =
{	{ '#',' ',' ',' ' },
	{ ' ','#',' ',' ' },
	{ ' ','#',' ',' ' },
	{ '#',' ',' ',' ' } };

PieceType chooseRandomPieceType();

void pieceWrite(const char ref[4][4], char obj[4][4]);
void blockWrite(const char ref[4][4], std::string* block);

class Piece {
public:
	Piece(PieceType chosen, Well* wl, const char graph[4][4]);
	virtual ~Piece();
	void move_down();
	PieceType pieceKind() const;
	int getX() const;
	int getY() const;
	std::string* get_graph() const;
	int get_orientation() const;
	int get_next_ori() const;
	virtual int leftmost() const = 0;
	virtual int rightmost() const = 0;
	virtual void rotate() = 0;
	virtual void move_right();
	virtual void move_left();

protected:
	void change_graph_to(const char ref[4][4]);
	void update_orientation();

private:
	PieceType m_piece;
	std::string* block;
	int orientation;
	int m_pos_x;
	int m_pos_y;
	Well* m_well;
};

class PieceI : public Piece {
public:
	PieceI(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceL : public Piece {
public:
	PieceL(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceJ : public Piece {
public:
	PieceJ(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceT : public Piece {
public:
	PieceT(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceO : public Piece {
public:
	PieceO(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceS : public Piece {
public:
	PieceS(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceZ : public Piece {
public:
	PieceZ(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceVapor : public Piece {
public:
	PieceVapor(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceFoam : public Piece {
public:
	PieceFoam(Well* well);
	virtual void rotate();
	virtual int leftmost() const;
	virtual int rightmost() const;
};

class PieceCrazy : public Piece {
public:
	PieceCrazy(Well* well);
	virtual void rotate();
	//actually move to left
	virtual void move_right();
	//actually move to right
	virtual void move_left();
	virtual int leftmost() const;
	virtual int rightmost() const;
};
#endif // PIECE_INCLUDED
