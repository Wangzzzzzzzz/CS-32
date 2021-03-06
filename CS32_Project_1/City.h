#ifndef CITY_H
#define CITY_H

#include "History.h"
#include "globals.h"

class Player;
class Flatulan;
//class History;

class City
{
public:
	// Constructor/destructor
	City(int nRows, int nCols);
	~City();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player *player() const;
	int     flatulanCount() const;
	int     nFlatulansAt(int r, int c) const;
	bool    isPlayerAt(int r, int c) const;
	bool    determineNewPosition(int& r, int& c, int dir) const;
	void    display() const;

	// Mutators
	bool  addFlatulan(int r, int c);
	bool  addPlayer(int r, int c);
	void  preachToFlatulansAroundPlayer();
	void  moveFlatulans();

	History& history();		//new function added

private:
	int       m_rows;
	int       m_cols;
	Player*   m_player;
	Flatulan* m_flatulans[MAXFLATULANS];
	History   m_history;	//new private member
	int       m_nFlatulans;

	// Helper functions
	bool isInBounds(int r, int c) const;
};

#endif
