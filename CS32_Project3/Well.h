#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include <string>


class Screen;
class Piece;


class Well
{
public:
	Well(int well_depth, int well_width);
	~Well();									//destructor
	void display(Screen& screen, int x, int y);
	bool addPiece();		//add a piece
	void updatePiece(Piece* another);		//after current piece is fixed, get a new piece
	bool canGoDown() const;	//to tell if the piece can continue going down
	bool canGoRight() const;		//check if a going-to-right command is valid;
	bool canGoLeft() const;		//check if a going-to-left command is valid;
	bool canRotate() const;		//check if a rotate command can be actaully done;
	void fix();				//to get a piece to rest
	bool moveDown();	//to tell if the piece can continue going down
	void moveRight();		//execute going-to-right command
	void moveLeft();		//execute going-to-left command
	void rotate();			//rotate the piece
	int  clean();			//clean the layers that are full, return the number of layer cleaned
	void discard();			//empty all element in the well
private:
	bool attemptOverWrite(int x, int y, const char graph[4][4]) const;	//test for overwrting a existing char or not
	bool attemptOverWrite(int x, int y, const std::string* graph) const;
	void FoamWrite(int cur_x, int cur_y, const int bomb_x, const int bomb_y);			// for fixation of the foam bomb
	void writePiece(int x, int y);
	void clearPiece();
	int m_depth;
	int m_width;
	Piece* curPiece;

	struct Layer {
		Layer(bool isBottom, int layer_width);	//constructor
		void write(int start_pos, const std::string reference, int length);	//write a part pf the layer
		void clear(int start_pos, int length);							//clear a part of a layer
		int  mutate(char org, char after);
		std::string display() const;		//display this layer
		bool empty();				//empty this layer
		void destroy();
		char getElement(int position) const;
		void updateFullness(int newFixed);
		int m_layer_width;
		char boundary;
		std::string m_array;
		bool m_isBottom;	//true if the layer is bottom
		bool m_isFull;		//true if the layer is full
		int m_filled;		//how many space is filled
	};

	Layer** m_layer;
	Layer* m_bottom;
};

#endif // WELL_INCLUDED
