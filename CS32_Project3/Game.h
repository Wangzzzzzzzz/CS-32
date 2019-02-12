#
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
// [Add other #include directives as necessary.]

int maximun(int comp1, int comp2);

class Game
{
  public:
    Game(int width, int height);
	~Game();
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void drawPiece();
	int get_score(int linesCleaned);
    // [Add other members as necessary.]

  private:
	Piece*  m_next_piece;
    Well	m_well;
    Screen  m_screen;
    int     m_level;
	int	    m_score;
	int     m_row_left;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
